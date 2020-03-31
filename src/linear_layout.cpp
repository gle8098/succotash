#include "linear_layout.hpp"
#include "view.hpp"


succotash::LinearLayout::LinearLayout(bool vertical)
  : is_vertical_(vertical)
{}

void succotash::LinearLayout::Place(const succotash::View *view_parent) {
  auto views = view_parent->GetSons();

  //sf::RectangleShape frame = view_parent->GetShape();
  auto parent_pos  = view_parent->GetShape().getPosition();
  auto parent_size = view_parent->GetShape().getSize();

  if (is_vertical_) {
    // Put views in a column

    //sf::Vector2f new_pos = frame.getPosition();
    //float x_step = new_pos.x / views.size();
    //sf::Vector2f view_size = sf::Vector2f(x_step, frame.getSize().y);

    float x_step = parent_size.x / views.size();
    sf::Vector2f new_pos(parent_pos.x, parent_pos.y);
    sf::Vector2f view_size = sf::Vector2f(x_step, parent_size.y);

    for (View* son : views) {
      son->MoveTo(new_pos);
      son->Resize(view_size);
      new_pos.x += x_step;
    }
  } else {
    // Put views in a row
    throw std::runtime_error("Not implemented");
  }
}

