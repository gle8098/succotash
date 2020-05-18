#ifndef DEFAULT_LAYOUT_HPP
#define DEFAULT_LAYOUT_HPP

#include <SFML/Graphics.hpp>

#include "layout.hpp"


namespace succotash {

class DefaultLayout : public Layout {
public:
  void Place(const std::vector<View*>& views,
             const sf::RectangleShape& area) override;

  LayoutParamsPtr CreateDefaultParams() const override;
  bool AreParametersOfMyClass(const LayoutParamsPtr params) const override;
};

struct DefaultLayoutParams : LayoutParams {
};

using DefaultLayoutPtr       = std::shared_ptr<DefaultLayout>;
using DefaultLayoutParamsPtr = std::shared_ptr<DefaultLayoutParams>;

} // succotash


#endif // DEFAULT_LAYOUT_HPP

