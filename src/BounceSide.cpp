#include "BounceSide.hpp"

namespace godot {

std::string bounceSideToText(BounceSide bounce) {
  auto it = labels.find(bounce);
  if (it == labels.end()) return std::string{"incorrect side"};

  return it->second;
}

}