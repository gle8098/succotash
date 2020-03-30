#include "window.hpp"


bool Window::HandleClick(const sf::Vector2i& click_pos) {
  return master_view_->HandleClick(click_pos);
}

void Window::DrawViews() {
  master_view_.Draw(*this);
}

