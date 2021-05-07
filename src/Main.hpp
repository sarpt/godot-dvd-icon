#pragma once

#include <Godot.hpp>
#include <Node.hpp>
#include <Sprite.hpp>

#include <string>

namespace godot {

class Main : public Node {
    GODOT_CLASS(Main, Node)

    Sprite* godotBounceIcon;
public:
    static void _register_methods();

    Main();
    ~Main();

    void _init(); // our initializer called by Godot
    void _ready();
    void _process(); // our initializer called by Godot
    void printPosition(Sprite* node, Vector2 newPosition);
    void printBounce(Sprite* node, int side);
};

}
