#include "linear_layout.hpp"
#include "view.hpp"
//#include "assert.hpp"

inline int GetWeight(succotash::View* son) {
  auto& plp = son->GetParentLayoutParams();
  auto weight_it = plp.find("weight");
  return weight_it != plp.end() ? atoi(weight_it->second.c_str()) : 1;
}

int GetTotalWeight(std::vector<succotash::View*>& sons) {
  int total_weight = 0;
  for (auto son : sons) {
    total_weight += GetWeight(son);
  }
  return total_weight;
}


namespace succotash {

LinearLayout::LinearLayout(Type orientation)
    : orientation_(orientation) {
}

void LinearLayout::Place(const succotash::View *parent_view) {
  auto views = parent_view->GetSons();
  int total_weight = GetTotalWeight(views);

  auto area_pos  = parent_view->GetShape().getPosition();
  auto area_size = parent_view->GetShape().getSize();

  size_t views_cnt = views.size();
  sf::Vector2f new_pos(area_pos.x, area_pos.y);

  if (orientation_ == Type::Horizontal) {  // Put views in a row.
    for (size_t i = 0; i < views_cnt; ++i) {
      View* view = views[i];
      double weight_ratio = (double) GetWeight(view) / total_weight;
      sf::Vector2f view_size(area_size.x * weight_ratio, area_size.y);

      view->MoveTo(new_pos);
      view->Resize(view_size);
      new_pos.x += view_size.x;
    }
  } else {  // Put views in a column.
    for (size_t i = 0; i < views_cnt; ++i) {
      View* view = views[i];
      double weight_ratio = (double) GetWeight(view) / total_weight;
      sf::Vector2f view_size(area_size.x, area_size.y * weight_ratio);

      view->MoveTo(new_pos);
      view->Resize(view_size);
      new_pos.y += view_size.y;
    }
  }
}

} // succotash
