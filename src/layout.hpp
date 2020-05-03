#ifndef SUCCOTASH_GRID_LAYOUT_HPP
#define SUCCOTASH_GRID_LAYOUT_HPP

#include "utilities/StringHashTable.hpp"
#include "utilities/Convertible.hpp"
// TODO: remove above include when will be possible

namespace succotash {

class View;

struct LayoutParams {
  using XmlParams = utilities::StringHashTable<utilities::Convertible>;

  virtual ~LayoutParams() = default;
};

class Layout {
protected:
  using XmlParams = utilities::StringHashTable<utilities::Convertible>;

public:
  virtual ~Layout() = default;

  virtual void Place(const View* view_parent) = 0;

  virtual LayoutParams* CreateDefaultParams() const = 0;
  virtual bool AreParametersOfMyClass(const LayoutParams* params) const = 0;
};

} // succotash

#endif // SUCCOTASH_GRID_LAYOUT_HPP
