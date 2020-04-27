#ifndef SUCCOTASH_LINEAR_LAYOUT_HPP
#define SUCCOTASH_LINEAR_LAYOUT_HPP

#include "layout.hpp"

namespace succotash {

class LinearLayout : public Layout {
public:
  enum Type {
    Vertical,
    Horizontal,
  };

  LinearLayout(Type orientation);
  void Place(const View* parent_view) override;

private:
  Type orientation_;
};

} // succotash

#endif // SUCCOTASH_LINEAR_LAYOUT_HPP
