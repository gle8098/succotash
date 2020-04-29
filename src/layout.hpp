#ifndef SUCCOTASH_GRID_LAYOUT_HPP
#define SUCCOTASH_GRID_LAYOUT_HPP


namespace succotash {

class View;

struct Layout {
  virtual ~Layout() = default;

  virtual void Place(const View* view_parent) = 0;
};

struct LayoutParams {
  virtual ~LayoutParams() = default;
};

} // succotash

#endif // SUCCOTASH_GRID_LAYOUT_HPP
