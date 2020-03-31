#include "window.hpp"
#include <SFML/System.hpp>

namespace succotash {

Window::Window(unsigned int width, unsigned int height) {
  create(sf::VideoMode(width, height), "Succotash");
  master_view_.GetViewShape().setPosition(0, 0);
  UpdateWindowSize();
}

void Window::DrawViews() { master_view_.Draw(*this); }

const View *Window::GetMasterView() const { return &master_view_; }
View *Window::GetMasterView() { return &master_view_; }

void Window::UpdateWindowSize() {
  auto size = getSize();
  master_view_.GetViewShape().setSize(sf::Vector2f(size.x, size.y));
}

} // succotash
