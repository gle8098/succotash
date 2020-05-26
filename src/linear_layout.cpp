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

float GetCriticalWidth(View* view) {
  auto params = std::dynamic_pointer_cast<LinearLayoutParams>(
      view->GetDispositionParams());
  return params->critical_width;
}

float GetCriticalHeight(View* view) {
  auto params = std::dynamic_pointer_cast<LinearLayoutParams>(
      view->GetDispositionParams());
  return params->critical_height;
}

float GetExpectedWidth(View* view, float area_width, float total_weight) {
  return area_width * GetWeight(view) / total_weight;
}

float GetExpectedHeight(View* view, float area_height, float total_weight) {
  return area_height * GetWeight(view) / total_weight;
}

bool IsCriticalWidth(View* view, float area_width, float total_weight) {
  return GetExpectedWidth(view, area_width, total_weight) <
         GetCriticalWidth(view);
}

bool IsCriticalHeight(View* view, float area_height, float total_weight) {
  return GetExpectedHeight(view, area_height, total_weight) <
         GetCriticalHeight(view);
}

float GetTotalWeight(const std::vector<View*>& sons) {
  float total_weight = 0;
  for (auto son : sons) {
    total_weight += GetWeight(son);
  }
  return total_weight;
}

void UpdateWidth(
    const std::vector<View*>& sons, sf::FloatRect& area, float &total_weight) {

  for (auto son : sons) {
    if (IsCriticalWidth(son, area.width, total_weight)) {
      area.width -= son->GetRect().width;
      total_weight -= GetWeight(son);
    }
  }
}

void UpdateHeight(
    const std::vector<View*>& sons, sf::FloatRect& area, float &total_weight) {

  for (auto son : sons) {
    if (IsCriticalHeight(son, area.height, total_weight)) {
      area.height -= son->GetRect().height;
      total_weight -= GetWeight(son);
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

      if (area.width > 0 && views.size() > 2) {
        int a;
        a += 5;
      }

      view->MoveTo(new_pos);
      if (IsCriticalWidth(view, area.width, total_weight)) {
        auto critical = GetCriticalWidth(view);
        new_pos.x += critical;
        view->Resize(sf::Vector2f(critical, area.height));

      printf("%.1f %.1f %.1f %.1f\n",
          view->GetRect().left, view->GetRect().top,
          view->GetRect().width, view->GetRect().height);

        continue;
      }

      sf::Vector2f view_size(
          GetExpectedWidth(view, area.width, total_weight), area.height);

      view->Resize(view_size);
      printf("%.1f %.1f %.1f %.1f\n",
          view->GetRect().left, view->GetRect().top,
          view->GetRect().width, view->GetRect().height);
      new_pos.x += view_size.x;
    }
  } else {  // Put views in a column.
    UpdateHeight(views, area, total_weight);

    for (size_t i = 0; i < views_cnt; ++i) {
      auto view = views[i];

      view->MoveTo(new_pos);

      if (IsCriticalHeight(view, area.height, total_weight)) {
        auto critical = GetCriticalHeight(view);
        new_pos.y += GetCriticalHeight(view);
        view->Resize(sf::Vector2f(area.width, critical));
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

  it = params.find("criticalWidth");
  if (it != params.end()) {
    critical_width = it->second.ToFloat();
  }

  it = params.find("criticalHeight");
  if (it != params.end()) {
    critical_height = it->second.ToFloat();
  }
}

} // succotash
