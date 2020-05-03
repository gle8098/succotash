#ifndef SUCCOTASH_LINEAR_LAYOUT_HPP
#define SUCCOTASH_LINEAR_LAYOUT_HPP

#include <SFML/Graphics.hpp>

#include "layout.hpp"
#include "view.hpp"


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
  LayoutParams* CreateDefaultParams() const override;
  bool AreParametersOfMyClass(const LayoutParams* params) const override;

private:
  Type orientation_;
};


struct LinearLayoutParams : LayoutParams {
  LinearLayoutParams() = default;
  LinearLayoutParams(const XmlParams& xml_params);

  int weight = 1;
};


} // succotash

#endif // SUCCOTASH_LINEAR_LAYOUT_HPP
