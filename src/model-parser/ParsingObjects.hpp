#ifndef SUCCOTASH_PARSINGOBJECTS_HPP
#define SUCCOTASH_PARSINGOBJECTS_HPP

#include <functional>
#include <pugixml.hpp>

#include "../utilities/Convertible.hpp"
#include "../utilities/StringHashTable.hpp"

// Objects which the parser recognizes
namespace succotash {
  class View;
  class Layout;
  class LayoutParams;
} // namespace succotash


namespace succotash::xml {

using utilities::StringHashTable;
using utilities::Convertible;

template <typename T>
using ObjectFactory = std::function< T* (const StringHashTable<Convertible>&) >;

struct LayoutFactories {
  ObjectFactory<Layout> layout_factory;
  ObjectFactory<LayoutParams> params_factory;
};

extern StringHashTable<ObjectFactory<View>> view_factories;
extern StringHashTable<LayoutFactories> layout_factories;

void InitFactories();

} // namespace succotash::xml

#endif  // SUCCOTASH_PARSINGOBJECTS_HPP
