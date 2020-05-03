#include "ParsingObjects.hpp"

#include "../button.hpp"
#include "../linear_layout.hpp"

namespace succotash::xml {

StringHashTable<ObjectFactory<View>> view_factories;
StringHashTable<LayoutFactories> layout_factories;

using Params = const StringHashTable<Convertible>&;

void InitFactories() {
  view_factories["View"]   = [] (Params params) { return new View(params);    };
  view_factories["Button"] = [] (Params params) { return new Button(params);  };

  layout_factories["LinearLayout"] = LayoutFactories {
      [] (Params params) { return new LinearLayout(params);       },
      [] (Params params) { return new LinearLayoutParams(params); }
  };
}

} // namespace succotash::xml
