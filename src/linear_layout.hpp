#ifndef SUCCOTASH_LINEAR_LAYOUT_HPP
#define SUCCOTASH_LINEAR_LAYOUT_HPP

#include "layout.hpp"

namespace succotash {

struct LinearLayout : Layout {
  LinearLayout(bool vertical);

  void Place(const View* view_parent) override;

private:
  bool is_vertical_;
};

} // succotash

#endif // SUCCOTASH_LINEAR_LAYOUT_HPP
