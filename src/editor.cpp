#include "editor.hpp"
#include <SFML/Graphics.hpp>

//using namespace succotash;
namespace succotash {

Editor::Editor()
    : window_(),
      current_tool_() {
}

void Editor::SetResolution(size_t width, size_t height) {
  window_.create(sf::VideoMode(width, height), "Succotash");
}

void Editor::Run() {
  while (window_.isOpen()) {
    sf::Event event{};
    while (window_.pollEvent(event)) {
      if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        window_.HandleClick(sf::Mouse::getPosition());
      }
    }
    window_.clear();
    window_.DrawViews();
    window_.display();
  }
}

}
