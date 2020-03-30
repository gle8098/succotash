#include "editor.hpp"
#include <SFML/Graphics.hpp>

namespace succotash {

Editor::Editor()
    : window_() {
}

void Editor::SetResolution(size_t width, size_t height) {
  window_.create(sf::VideoMode(width, height), "Succotash");
}

void Editor::Run() {
  while (window_.isOpen()) {
    sf::Event event{};
    while (window_.pollEvent(event)) {
      if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        HandleClick(sf::Mouse::getPosition());
      }
    }
    window_.clear();
    window_.DrawViews();
    window_.display();
  }
}

void Editor::HandleClick(const sf::Vector2i& mouse_pos) {
  View* master_view = window_.GetMasterView();
  View* cur_view = master_view;

  // 1. Find clicked View. Go down in the tree.
  bool clicked_view_found = false;
  while (!clicked_view_found) {
    // Iterate for every son & check if click within its bounds
    for (View *son : cur_view->GetSons()) {
      if (son->IsPointWithinBounds(mouse_pos)) {
        cur_view = son;
        break;
      }
    }
    // It wasn't clicked on any son of mine => clicked on me
    clicked_view_found = true;
  }

  // 2. Propagate mouse event
  View* original_clicked_view = cur_view;
  do {
    if (cur_view->OnClickEvent(original_clicked_view)) {
      return;
    }
    cur_view = cur_view->GetParent();
  } while (cur_view != master_view);
}

}  // succotash
