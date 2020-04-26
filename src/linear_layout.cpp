#include "linear_layout.hpp"
#include "view.hpp"
#include "assert.hpp"


namespace succotash {

LinearLayout::LinearLayout(Type orientation)
    : orientation_(orientation),
      weights_()
{}

void LinearLayout::Place(const succotash::View *parent_view) {
  auto views = parent_view->GetSons();
  ASSERT(views.size() == weights_.size());

  auto area_pos  = parent_view->GetShape().getPosition();
  auto area_size = parent_view->GetShape().getSize();

  if (orientation_ == Type::Horizontal) {  // Put views in a row.
    float x_step = area_size.x / views.size();
    sf::Vector2f new_pos(area_pos.x, area_pos.y);
    sf::Vector2f view_size = sf::Vector2f(x_step, area_size.y);

    size_t iter = 0;
    for (View* son : views) {

      son->MoveTo(new_pos);
      son->Resize(view_size);
      new_pos.x += x_step;
    }
  } else {  // Put views in a column.
    float y_step = area_size.y / views.size();
    sf::Vector2f new_pos(area_pos.x, area_pos.y);
    sf::Vector2f view_size = sf::Vector2f(area_size.x, y_step);

    for (View* son : views) {
      son->MoveTo(new_pos);
      son->Resize(view_size);
      new_pos.y += y_step;
    }
  }
}

void LinearLayout::SetWeights(std::vector<int>& weights) {
  weights_ = std::move(weights);
}

} // succotash
