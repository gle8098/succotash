#include "ParsingObjects.hpp"

#include "../button.hpp"
#include "../linear_layout.hpp"
#include "../view.hpp"
#include "../layout.hpp"

namespace succotash::xml {

StringHashTable<ObjectFactory<View>> kViewFactories;
StringHashTable<ObjectFactory<Layout>> kLayoutFactories;

using Params = ObjectParams&;

void InitFactories() {
  kViewFactories["View"] = [] (Params params) {
    auto* view = new View();
    if (params.find("id") != params.end()) {
      view->SetId(params.at("id").as_int());
    }
    return view;
  };
  kViewFactories["Button"] = [] (Params params) {
    auto sf_name = sf::String(params.at("name").value());
    auto* view = new Button(sf_name);
    if (params.find("id") != params.end()) {
      view->SetId(params.at("id").as_int());
    }
    return view;
  };

  kLayoutFactories["LinearLayout"] = [] (Params params) {
    bool is_horizontal = std::string(params.at("orientation").value()) == "horizontal";
    return new LinearLayout(is_horizontal ? LinearLayout::Type::Horizontal : LinearLayout::Type::Vertical);
  };
}

} // namespace succotash::xml
