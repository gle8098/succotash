#ifndef SUCCOTASH_GRID_LAYOUT_HPP
#define SUCCOTASH_GRID_LAYOUT_HPP


namespace succotash {

class View;

struct LayoutParams {
  virtual ~LayoutParams() = default;
};

struct Layout {
  virtual ~Layout() = default;

  virtual void Place(const View* view_parent) = 0;

  virtual LayoutParams* CreateDefaultParams() const = 0;
  virtual bool AreParametersOfMyClass(const LayoutParams* params) const = 0;
};

} // succotash

#endif // SUCCOTASH_GRID_LAYOUT_HPP
