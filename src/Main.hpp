#pragma once

#include <Godot.hpp>
#include <Node.hpp>
#include <Sprite.hpp>

namespace godot {

class Main : public Node {
  GODOT_CLASS(Main, Node)

  Sprite* godotBounceIcon;
public:
  static void _register_methods();

  Main();
  ~Main();

  void _init();
  void _ready();
  void _process();
  void printPosition(Sprite* node, Vector2 newPosition);
  void printBounce(Sprite* node, int side);
};

}
