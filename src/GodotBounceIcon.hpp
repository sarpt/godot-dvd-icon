#pragma once

#include <Godot.hpp>
#include <Sprite.hpp>
#include <Timer.hpp>

#include <string>

namespace godot {

enum BounceSide {
    Floor,
    Ceiling,
    Right,
    Left
};

class GodotBounceIcon : public Sprite {
    GODOT_CLASS(GodotBounceIcon, Sprite)

    float xlimit, ylimit;
    float xperiod, yperiod;
    float time_passed;
    float speed;
    Vector2 position;
    bool directionDown, directionRight;
    Timer *printTimer;

    void updateLimits();
    void updatePeriods(float speed, float xlimit, float ylimit);
    void updatePosition(float time_passed, float xlimit, float ylimit, float xperiod, float yperiod);
    void updateDirections(float time_passed, float xperiod, float yperiod);
    static float moveOnAxis(float time, float positionLimit, float fullCycleTime);
    static float triangleWave(float x, float amplitude, float period);
    bool squareWave(float x, float period);

public:
    static void _register_methods();

    GodotBounceIcon();
    ~GodotBounceIcon();

    void _init(); // our initializer called by Godot
    void _ready();

    void _process(float delta);
    void setSpeed(float speed);
    float getSpeed() const;
    
    void emitBounce(BounceSide side);
    void emitPosition();
};

}
