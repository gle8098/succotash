#include "window.hpp"
#include <SFML/System.hpp>

using namespace succotash;

bool Window::HandleClick(const sf::Vector2i& click_pos) {
  return master_view_.HandleClick(click_pos);
}

void Window::DrawViews() {
  master_view_.Draw(*this);
}

