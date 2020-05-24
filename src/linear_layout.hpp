#ifndef SUCCOTASH_LINEAR_LAYOUT_HPP
#define SUCCOTASH_LINEAR_LAYOUT_HPP

#include <SFML/Graphics.hpp>

#include "layout.hpp"


namespace succotash {


class LinearLayout : public Layout {
public:
  enum Type {
    Vertical,
    Horizontal,
  };

public:
  LinearLayout(Type orientation);
  LinearLayout(const XmlParams& xml_params);

  void Place(const std::vector<View*>& views,
             const sf::RectangleShape& area) override;
  LayoutParamsPtr CreateDefaultParams() const override;
  bool AreParametersOfMyClass(const LayoutParamsPtr params) const override;

private:
  Type orientation_;
};


struct LinearLayoutParams : LayoutParams {
  LinearLayoutParams() = default;
  LinearLayoutParams(const XmlParams& xml_params);

  float weight = 1.0;
};

using LinearLayoutPtr       = std::shared_ptr<LinearLayout>;
using LinearLayoutParamsPtr = std::shared_ptr<LinearLayoutParams>;

} // succotash

#endif // SUCCOTASH_LINEAR_LAYOUT_HPP
