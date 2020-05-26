#include "default_layout.hpp"

#include "view.hpp"
#include "utilities/assert.hpp"


namespace succotash {

void DefaultLayout::Place(const std::vector<View*>& views,
                          sf::FloatRect&& area) {
  if (views.size() > 1) {
    WARNING("default layout cannot handle more than one view");
  }
  for (auto view : views) {  // Fit views to area
    view->MoveTo(sf::Vector2f(area.left, area.top));
    view->Resize(sf::Vector2f(area.width, area.height));
  }
}

LayoutParamsPtr DefaultLayout::CreateDefaultParams() const {
  return std::make_shared<LayoutParams>();
}

bool DefaultLayout::AreParametersOfMyClass(const LayoutParamsPtr params) const {
  return false;
}

} // succotash

