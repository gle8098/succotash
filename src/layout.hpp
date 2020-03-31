#ifndef SUCCOTASH_GRID_LAYOUT_HPP
#define SUCCOTASH_GRID_LAYOUT_HPP

namespace succotash {

class View;


struct Layout {
  virtual void Place(const View* view_parent) = 0;
};

} // succotash

#endif // SUCCOTASH_GRID_LAYOUT_HPP
