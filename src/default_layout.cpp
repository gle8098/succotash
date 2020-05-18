#include "default_layout.hpp"

#include "view.hpp"
#include "utilities/assert.hpp"


namespace succotash {

void DefaultLayout::Place(const std::vector<View*>& views,
           const sf::RectangleShape& area) {
  if (views.size() > 1) {
    WARNING("default layout cannot handle more than one view");
  }
  for (auto view : views) {  // Fit views to area
    view->MoveTo(area.getPosition());
    view->Resize(area.getSize());
  }
}

LayoutParamsPtr DefaultLayout::CreateDefaultParams() const {
  return std::make_shared<LayoutParams>();
}

bool DefaultLayout::AreParametersOfMyClass(const LayoutParamsPtr params) const {
  return false;
}

} // succotash

