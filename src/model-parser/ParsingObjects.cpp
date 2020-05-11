#include "ParsingObjects.hpp"

#include "../button.hpp"
#include "../linear_layout.hpp"

namespace succotash::xml {

StringHashTable<ObjectFactory<View>> view_factories;
StringHashTable<LayoutFactories> layout_factories;

using Params = const StringHashTable<Convertible>&;

void InitFactories() {
  view_factories["View"]   = [] (Params params) {
    return std::make_shared<View>(params);
  };
  view_factories["Button"] = [] (Params params) {
    return std::make_shared<Button>(params);
  };

  layout_factories["LinearLayout"] = LayoutFactories {
      [] (Params params) { return std::make_shared<LinearLayout>(params);       },
      [] (Params params) { return std::make_shared<LinearLayoutParams>(params); }
  };
}

} // namespace succotash::xml
