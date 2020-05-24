#include "linear_layout.hpp"
#include "view.hpp"

namespace succotash {

//------------------------------------------------------------------------------
// Local functions.
//------------------------------------------------------------------------------

inline float GetWeight(View* view) {
  auto params = std::dynamic_pointer_cast<LinearLayoutParams>(
      view->GetDispositionParams());
  return params->weight;
}

float GetTotalWeight(const std::vector<View*>& sons) {
  float total_weight = 0;
  for (auto son : sons) {
    total_weight += GetWeight(son);
  }
  return total_weight;
}

//------------------------------------------------------------------------------
// Ctors.
//------------------------------------------------------------------------------

LinearLayout::LinearLayout(Type orientation)
    : orientation_(orientation) {
}

LinearLayout::LinearLayout(const XmlParams& params) {
  orientation_ = params.at("orientation") == "horizontal" ?
    LinearLayout::Type::Horizontal :
    LinearLayout::Type::Vertical;
}

//------------------------------------------------------------------------------
// Methods.
//------------------------------------------------------------------------------

void LinearLayout::Place(const std::vector<View*>& views,
                         const sf::RectangleShape& area) {
  float total_weight = GetTotalWeight(views);

  auto area_pos  = area.getPosition();
  auto area_size = area.getSize();

  size_t views_cnt = views.size();
  sf::Vector2f new_pos(area_pos.x, area_pos.y);

  if (orientation_ == Type::Horizontal) {  // Put views in a row.
    for (size_t i = 0; i < views_cnt; ++i) {
      auto view = views[i];
      double weight_ratio = (double) GetWeight(view) / total_weight;
      sf::Vector2f view_size(area_size.x * weight_ratio, area_size.y);

      view->MoveTo(new_pos);
      view->Resize(view_size);
      new_pos.x += view_size.x;
    }
  } else {  // Put views in a column.
    for (size_t i = 0; i < views_cnt; ++i) {
      auto view = views[i];
      double weight_ratio = (double) GetWeight(view) / total_weight;
      sf::Vector2f view_size(area_size.x, area_size.y * weight_ratio);

      view->MoveTo(new_pos);
      view->Resize(view_size);
      new_pos.y += view_size.y;
    }
  }
}

LayoutParamsPtr LinearLayout::CreateDefaultParams() const {
  return std::make_shared<LinearLayoutParams>();
}

bool LinearLayout::AreParametersOfMyClass(LayoutParamsPtr params) const {
  return (bool)std::dynamic_pointer_cast<LinearLayoutParams>(params);
}

LinearLayoutParams::LinearLayoutParams(const XmlParams& params) {
  auto weight_it = params.find("weight");
  weight = weight_it != params.end() ?  weight_it->second.ToFloat() : 1.0;
}

} // succotash
