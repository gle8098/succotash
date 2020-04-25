#include "editor.hpp"

#include <SFML/Graphics.hpp>


namespace succotash {

Editor::Editor()
    : display_(sf::VideoMode(800, 600), "Succotash") {

  display_.setFramerateLimit(50);

  master_view_.MoveTo(sf::Vector2f(0, 0));
  master_view_.Resize(sf::Vector2f(800, 600));  // tmp
}

void Editor::Run() {

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

void Editor::HandleClick(const sf::Event::MouseButtonEvent& mouse_pos) {
  View* cur_view = &master_view_;

  // 1. Find clicked View. Go down in the tree.
  bool clicked_view_found = false;
  while (!clicked_view_found) {
    // Iterate for every son & check if click within its bounds
    for (View *son : cur_view->GetSons()) {
      if (son->IsPointWithinBounds(sf::Vector2i(mouse_pos.x, mouse_pos.y))) {
        cur_view = son;
        break;
      }
    }
    // It wasn't clicked on any son of mine => clicked on me
    clicked_view_found = true;
  }

  // 2. Propagate mouse event
  View* original_clicked_view = cur_view;
  while (cur_view != nullptr) {
    if (cur_view->OnClickEvent(original_clicked_view)) {
      return;
    }
    cur_view = cur_view->GetParent();
  }
}

const View& Editor::GetMasterView() const { return master_view_; }
View&       Editor::GetMasterView()       { return master_view_; }

}  // succotash

