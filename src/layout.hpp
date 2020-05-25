#ifndef SUCCOTASH_LAYOUT_HPP
#define SUCCOTASH_LAYOUT_HPP

#include <vector>
#include <memory>

#include "utilities/StringHashTable.hpp"
#include "utilities/Convertible.hpp"
// TODO: remove above include when will be possible

namespace succotash {

class Layout;
using LayoutPtr = std::shared_ptr<Layout>;

class LayoutParams;
using LayoutParamsPtr = std::shared_ptr<LayoutParams>;

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

  virtual void Place(const std::vector<View*>& views,
                     const sf::FloatRect&& area) = 0;

  virtual LayoutParamsPtr CreateDefaultParams() const = 0;
  virtual bool AreParametersOfMyClass(const LayoutParamsPtr params) const = 0;
};

} // succotash

#endif // SUCCOTASH_LAYOUT_HPP
