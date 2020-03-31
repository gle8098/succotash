#include "linear_layout.hpp"
#include "view.hpp"

succotash::LinearLayout::LinearLayout(bool vertical)
  : is_vertical_(vertical)
{}

void succotash::LinearLayout::Place(const succotash::View *view_parent) {
  auto parent_pos  = view_parent->GetViewShape().getPosition();
  auto parent_size = view_parent->GetViewShape().getSize();

  if (is_vertical_) {
    // Put views in a column
    float x_step = parent_size.x / view_parent->GetSons().size();
    float current_x = parent_pos.x;

    for (View* son : view_parent->GetSons()) {
      auto& shape = son->GetViewShape();
      shape.setPosition(sf::Vector2f(current_x, parent_pos.y));
      shape.setSize(sf::Vector2f(x_step, parent_size.y));
      current_x += x_step;
    }
  } else {
    // Put views in a row
    throw std::runtime_error("Not implemented");
  }
}

