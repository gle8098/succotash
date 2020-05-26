#include "linear_layout.hpp"
#include "view.hpp"

namespace succotash {

//------------------------------------------------------------------------------
// Local functions.
//------------------------------------------------------------------------------

float GetWeight(View* view) {
  auto params = std::dynamic_pointer_cast<LinearLayoutParams>(
      view->GetDispositionParams());
  return params->weight;
}

float GetExpectedWidth(View* view, float area_width, float total_weight) {
  return area_width * GetWeight(view) / total_weight;
}

float GetExpectedHeight(View* view, float area_height, float total_weight) {
  return area_height * GetWeight(view) / total_weight;
}

bool HasFixedWidth(View* view) {
  return view->GetFixedSize().x != 0;
}

bool HasFixedHeight(View* view) {
  return view->GetFixedSize().y != 0;
}

float GetTotalWeight(const std::vector<View*>& sons) {
  float total_weight = 0;
  for (auto son : sons) {
    total_weight += GetWeight(son);
  }
  return total_weight;
}

void UpdateWidth(
    const std::vector<View*>& views, sf::FloatRect& area, float &total_weight) {

  for (auto view : views) {
    if (HasFixedWidth(view)) {
      area.width -= view->GetRect().width;
      total_weight -= GetWeight(view);
    }
  }
}

void UpdateHeight(
    const std::vector<View*>& views, sf::FloatRect& area, float &total_weight) {

  for (auto view : views) {
    if (HasFixedHeight(view)) {
      area.height -= view->GetRect().height;
      total_weight -= GetWeight(view);
    }
  }
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
                         sf::FloatRect&& area) {

  float total_weight = GetTotalWeight(views);

  size_t views_cnt = views.size();
  sf::Vector2f new_pos(area.left, area.top);

  if (orientation_ == Type::Horizontal) {  // Put views in a row.
    UpdateWidth(views, area, total_weight);

    for (size_t i = 0; i < views_cnt; ++i) {
      auto view = views[i];

      view->MoveTo(new_pos);

      if (HasFixedWidth(view)) {
        auto fixed = view->GetFixedSize().x;
        new_pos.x += fixed;
        view->Resize(sf::Vector2f(fixed, area.height));
        continue;
      }

      sf::Vector2f view_size(
          GetExpectedWidth(view, area.width, total_weight), area.height);

      view->Resize(view_size);
      //printf("%.1f %.1f %.1f %.1f\n",
      //    view->GetRect().left, view->GetRect().top,
      //    view->GetRect().width, view->GetRect().height);
      new_pos.x += view_size.x;
    }
  } else {  // Put views in a column.
    UpdateHeight(views, area, total_weight);

    for (size_t i = 0; i < views_cnt; ++i) {
      auto view = views[i];

      view->MoveTo(new_pos);

      if (HasFixedHeight(view)) {
        auto fixed = view->GetFixedSize().y;
        new_pos.y += fixed;
        view->Resize(sf::Vector2f(area.width, fixed));
        continue;
      }

      sf::Vector2f view_size(
          area.width, GetExpectedWidth(view, area.height, total_weight));
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
  auto it = params.find("weight");
  if (it != params.end()) {
    weight = it->second.ToFloat();
  }
}

} // succotash
