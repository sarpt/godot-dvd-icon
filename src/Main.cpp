#include "Main.hpp"

#include "BounceSide.hpp"

#include "Sprite.hpp"

using namespace godot;

void Main::_register_methods() {
  register_method("_process", &Main::_process);
  register_method("_ready", &Main::_ready);
  register_method("printPosition", &Main::printPosition);
  register_method("printBounce", &Main::printBounce);
}

Main::Main() {}

Main::~Main() {}

void Main::_init() {}

void Main::_ready() {
  godotBounceIcon = get_node<Sprite>("GodotBounceIcon");
  godotBounceIcon->connect("position_changed", this, "printPosition");
  godotBounceIcon->connect("bounced", this, "printBounce");
}

void Main::_process() {
}

void Main::printPosition(Sprite* node, Vector2 newPosition) {
  Godot::print("The position of " + node->get_name() + " is " + String::num_real(newPosition.x) + ";" + String::num_real(newPosition.y));
}

void Main::printBounce(Sprite* node, int side) {
  auto bounceText = String{bounceSideToText(static_cast<BounceSide>(side)).c_str()};
  Godot::print("Bounce " + bounceText);
}