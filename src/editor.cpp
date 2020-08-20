#include "editor.hpp"

#include <SFML/Graphics.hpp>

#include <iostream> //debug

namespace succotash {

Editor::Editor()
    : display_(sf::VideoMode(1920, 1080), "Succotash") {

  display_.setFramerateLimit(50);

  master_view_.MoveTo(sf::Vector2f(0, 0));
  master_view_.Resize(sf::Vector2f(display_.getSize()));
}

void Editor::Run() {
  sf::FloatRect visibleArea;
  while (display_.isOpen()) {
    sf::Event event;

    while (display_.pollEvent(event)) {
      switch (event.type) {

      case sf::Event::Closed:
        display_.close();
        break;

      case sf::Event::MouseButtonPressed:
        if (event.mouseButton.button == sf::Mouse::Left) {
          HandleClick(event.mouseButton);
        }
        break;

      case sf::Event::Resized:
        {
          sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
          display_.setView(sf::View(visibleArea));
          master_view_.Resize(
              sf::Vector2f(event.size.width, event.size.height));
          break;
        }

      default:
        break;
      }
    }
    // Redraw window
    display_.clear();
    master_view_.Draw(display_);
    display_.display();
  }
}

void Editor::HandleClick(const sf::Event::MouseButtonEvent& click) {
  master_view_.HandleClick(sf::Vector2i(click.x, click.y));
}

const View* Editor::GetMasterView() const { return &master_view_; }
View*       Editor::GetMasterView()       { return &master_view_; }

}  // succotash
