#include "editor.hpp"
#include <SFML/Graphics.hpp>

namespace succotash {

Window *Editor::GetWindow() { return &window_; }
const Window *Editor::GetWindow() const { return &window_; }

void Editor::Run() {
  while (window_.isOpen()) {
    // Redraw window
    window_.clear();
    window_.DrawViews();
    window_.display();

    // Wait for event
    sf::Event event{};
    //printf("Waiting event... "); fflush(stdout);
    window_.waitEvent(event);
    //printf("Event type %d\n", event.type);

    switch (event.type) {
    case sf::Event::Closed:
      window_.close();
      break;

    case sf::Event::MouseButtonPressed:
      if (event.mouseButton.button == sf::Mouse::Left) {
        HandleClick(event.mouseButton);
      }
      break;
    }
  }
}

void Editor::HandleClick(const sf::Event::MouseButtonEvent& mouse_pos) {
  View* master_view = window_.GetMasterView();
  View* cur_view = master_view;

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

}  // succotash
