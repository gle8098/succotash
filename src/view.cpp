#include "view.hpp"

bool succotash::View::HandleClick(const sf::Vector2i &pos) const {
  if (!this->getGlobalBounds().contains(pos)) {
    // todo: this if converts pos.{x,y} to float
    return false;
  }

  for (View *son : sons_) {
    if (son->HandleClick(pos)) {
      return true;
    }
  }

  //if ()
}

void succotash::View::DrawSelf() const {}
