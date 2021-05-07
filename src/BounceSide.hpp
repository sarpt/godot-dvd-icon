#pragma once

#include <map>
#include <string>
#include <utility>

namespace godot {

enum BounceSide {
    Floor,
    Ceiling,
    Right,
    Left
};

const std::map<BounceSide, std::string> labels{
  std::make_pair(Floor, std::string{"floor"}),
  std::make_pair(Ceiling, std::string{"ceiling"}),
  std::make_pair(Right, std::string{"right"}),
  std::make_pair(Left, std::string{"left"})
};

std::string bounceSideToText(BounceSide bounce);

}
