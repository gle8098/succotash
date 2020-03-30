#ifndef SUCCOTASH_LAYOUT_HPP
#define SUCCOTASH_LAYOUT_HPP

namespace succotash {
class View;

struct Layout {
  virtual void Place(View *view) = 0;
};
}

#endif // SUCCOTASH_LAYOUT_HPP
