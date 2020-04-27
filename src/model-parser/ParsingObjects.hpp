#ifndef SUCCOTASH_PARSINGOBJECTS_HPP
#define SUCCOTASH_PARSINGOBJECTS_HPP

#include <StringHashTable.hpp>
#include <functional>
#include <pugixml.hpp>

namespace succotash {

class View;
class Layout;

namespace xml {

using ObjectParams = const StringHashTable<pugi::xml_attribute>;
template <typename T> using ObjectFactory = std::function<T*(ObjectParams&)>;

extern StringHashTable<ObjectFactory<View>> kViewFactories;
extern StringHashTable<ObjectFactory<Layout>> kLayoutFactories;

void InitFactories();

} // namespace xml

} // namespace succotash

#endif  // SUCCOTASH_PARSINGOBJECTS_HPP
