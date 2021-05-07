#include "GodotBounceIcon.hpp"

#include "BounceSide.hpp"

#include <Viewport.hpp>

#include <cmath>

using namespace godot;

void GodotBounceIcon::_register_methods() {
  register_method("_process", &GodotBounceIcon::_process);
  register_method("_ready", &GodotBounceIcon::_ready);
  register_method("emitPosition", &GodotBounceIcon::emitPosition);
  register_property<GodotBounceIcon, float>("speed", &GodotBounceIcon::setSpeed, &GodotBounceIcon::getSpeed, 5);
  register_signal<GodotBounceIcon>("position_changed", "node", GODOT_VARIANT_TYPE_OBJECT, "new_pos", GODOT_VARIANT_TYPE_VECTOR2);
  register_signal<GodotBounceIcon>("bounced", "node", GODOT_VARIANT_TYPE_OBJECT, "side", GODOT_VARIANT_TYPE_INT);
}

GodotBounceIcon::GodotBounceIcon() {
}

GodotBounceIcon::~GodotBounceIcon() {
  // printTimer->disconnect("timeout", this, "emitPosition"); // TODO: timer is cleaned up before Icon is cleaned up, need to check for existence during cleanup
}

void GodotBounceIcon::_init() {
  time_passed = 0.0;
  speed = 5;
  position = Vector2();
  directionRight = true;
  directionDown = true;
}

void GodotBounceIcon::_ready() {
  printTimer = get_node<Timer>("PositionTimer");
  printTimer->connect("timeout", this, "emitPosition");
}

void GodotBounceIcon::_process(float delta) {
  time_passed += delta;

  updateLimits();
  updatePeriods(speed, xlimit, ylimit);
  updatePosition(time_passed, xlimit, ylimit, xperiod, yperiod);

  auto prevDirectionRight = directionRight;
  auto prevDirectionDown = directionDown;

  updateDirections(time_passed, xperiod, yperiod);
  checkForBounce(prevDirectionDown, directionDown, prevDirectionRight, directionRight);
}

void GodotBounceIcon::checkForBounce(bool prevDown, bool down, bool prevRight, bool right) {
  if (prevRight && !right) emitBounce(BounceSide::Right);
  if (!prevRight && right) emitBounce(BounceSide::Left);
  if (prevDown && !down) emitBounce(BounceSide::Floor);
  if (!prevDown && down) emitBounce(BounceSide::Ceiling);
}

void GodotBounceIcon::updateLimits() {
  auto viewport = get_viewport();
  auto xsize = viewport->get_size().x;
  auto ysize = viewport->get_size().y;

  xlimit = xsize - get_rect().get_size().x;
  ylimit = ysize - get_rect().get_size().y;
}

void GodotBounceIcon::updatePeriods(float speed, float xlimit, float ylimit) {
  auto slowestSpeedSecondsPerPixel = 0.043;
  xperiod = 1 * ((xlimit / 2) * slowestSpeedSecondsPerPixel / speed);
  yperiod = 0.77 * ((ylimit / 2) * slowestSpeedSecondsPerPixel / speed);
}

void GodotBounceIcon::updatePosition(float time_passed, float xlimit, float ylimit, float xperiod, float yperiod) {
  position.x = GodotBounceIcon::moveOnAxis(time_passed, xlimit, xperiod);
  position.y = GodotBounceIcon::moveOnAxis(time_passed, ylimit, yperiod);

  set_position(position);
}

// updateDirections uses derivative of triangle wave - square function with doubled period of a triangle (due to abs() used on a triangle)
void GodotBounceIcon::updateDirections(float time_passed, float xperiod, float yperiod) {
  directionRight = GodotBounceIcon::squareWave(time_passed, xperiod / 4);
  directionDown = GodotBounceIcon::squareWave(time_passed, yperiod / 4);
}

float GodotBounceIcon::moveOnAxis(float time, float positionLimit, float fullCycleSeconds) {
  auto oneCycleSeconds = fullCycleSeconds / 2;

  return std::abs(GodotBounceIcon::triangleWave(time, positionLimit, oneCycleSeconds));
}

float GodotBounceIcon::triangleWave(float x, float amplitude, float period) {
  return (2 * amplitude / 3.14) * std::asin(std::sin(2 * (3.14 / period) * x));
}

bool GodotBounceIcon::squareWave(float x, float period) {
  return !std::signbit(std::sin((2 * 3.14 * x) / period));
}

void GodotBounceIcon::setSpeed(float newSpeed) {
  speed = newSpeed;
}

float GodotBounceIcon::getSpeed() const {
  return speed;
}

void GodotBounceIcon::emitBounce(BounceSide side) {
  emit_signal("bounced", this, side);
}

void GodotBounceIcon::emitPosition() {
  emit_signal("position_changed", this, position);
}
