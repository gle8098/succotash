#include "linear_layout.hpp"
#include "view.hpp"
#include "utilities/Convertible.hpp"


inline int GetWeight(succotash::View* son) {
  auto* params = dynamic_cast<const succotash::LinearLayoutParams*>(
      son->GetDispositionParams());
  return params->weight;
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

LinearLayout::LinearLayout(const XmlParams& params) {
  orientation_ = params.at("orientation") == "horizontal" ?
    LinearLayout::Type::Horizontal :
    LinearLayout::Type::Vertical;
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

LayoutParams* LinearLayout::CreateDefaultParams() const {
  return new LinearLayoutParams;
}

bool LinearLayout::AreParametersOfMyClass(const LayoutParams* params) const {
  return dynamic_cast<const LinearLayoutParams*>(params) != nullptr;
}

LinearLayoutParams::LinearLayoutParams(const XmlParams& params) {
  auto weight_it = params.find("weight");
  weight = weight_it != params.end() ?  weight_it->second.ToInt() : 1;
}

} // succotash
