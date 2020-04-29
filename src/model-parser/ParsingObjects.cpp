#include "ParsingObjects.hpp"

#include "../button.hpp"
#include "../linear_layout.hpp"

namespace succotash::xml {

StringHashTable<ObjectFactory<View>> view_factories;
StringHashTable<LayoutFactories> layout_factories;

using Params = const StringHashTable<Convertible>&;

void InitFactories() {
  view_factories["View"]   = [] (Params params) { return View  ::Construct(params); };
  view_factories["Button"] = [] (Params params) { return Button::Construct(params); };

  layout_factories["LinearLayout"] = LayoutFactories {
      [] (Params params) { return LinearLayout      ::Construct(params); },
      [] (Params params) { return LinearLayoutParams::Construct(params); }
  };
}

} // namespace succotash::xml
