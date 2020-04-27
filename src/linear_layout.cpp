#include "linear_layout.hpp"
#include "view.hpp"
//#include "assert.hpp"


int GetTotalWeight(std::vector<int>& weights) {
  int total_weight = 0;
  for (int item_weight : weights) {
    total_weight += item_weight;
  }
  return total_weight;
}


namespace succotash {

LinearLayout::LinearLayout(Type orientation)
    : orientation_(orientation),
      weights_()
{}

void LinearLayout::Place(std::vector<View*>& views,
                         const sf::RectangleShape& area) {
  if (views.size() != weights_.size()) {
    weights_.resize(views.size(), 1); // Append ones or remove weights tail.
  }

  auto area_pos  = area.getPosition();
  auto area_size = area.getSize();

  int total_weight = GetTotalWeight(weights_);

  size_t views_cnt = views.size();
  sf::Vector2f new_pos(area_pos.x, area_pos.y);

  if (orientation_ == Type::Horizontal) {  // Put views in a row.
    for (size_t i = 0; i < views_cnt; ++i) {
      View* view = views[i];
      double weight_ratio = (double)weights_[i] / total_weight;
      sf::Vector2f view_size(area_size.x * weight_ratio, area_size.y);

      view->MoveTo(new_pos);
      view->Resize(view_size);
      new_pos.x += view_size.x;
    }
  } else {  // Put views in a column.
    for (size_t i = 0; i < views_cnt; ++i) {
      View* view = views[i];
      double weight_ratio = (double)weights_[i] / total_weight;
      sf::Vector2f view_size(area_size.x, area_size.y * weight_ratio);

      view->MoveTo(new_pos);
      view->Resize(view_size);
      new_pos.y += view_size.y;
    }
  }
}

void LinearLayout::SetWeights(std::vector<int>& weights) {
  weights_ = std::move(weights);
}
void LinearLayout::SetWeights(std::vector<int>&& weights) {
  weights_ = std::move(weights);
}

} // succotash
