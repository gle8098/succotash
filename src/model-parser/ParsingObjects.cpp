#include "ParsingObjects.hpp"

#include "../view.hpp"
#include "../button.hpp"
#include "../pane.hpp"
#include "../linear_layout.hpp"

namespace succotash::xml {

StringHashTable<ObjectFactoryRaw<View>> view_factories;
StringHashTable<LayoutFactories> layout_factories;

using Params = const StringHashTable<Convertible>&;

void InitFactories() {
  view_factories["View"]   = [] (Params params) {
    return new View(params);
  };
  view_factories["Button"] = [] (Params params) {
    return new Button(params);
  };

  // Pane.
  view_factories["Pane"] = [] (Params params) {
    return new Pane(params);
  };
  view_factories["Tab"] = [] (Params params) {
    return new Tab(params);
  };
  // Aliases for parser tab content.
  view_factories["Head"] = [] (Params params) {
    return new View(params);
  };
  view_factories["Body"] = [] (Params params) {
    return new View(params);
  };

  layout_factories["LinearLayout"] = LayoutFactories {
      [] (Params params) { return std::make_shared<LinearLayout>(params);       },
      [] (Params params) { return std::make_shared<LinearLayoutParams>(params); }
  };
}

} // namespace succotash::xml
