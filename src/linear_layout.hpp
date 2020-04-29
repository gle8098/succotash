#ifndef SUCCOTASH_LINEAR_LAYOUT_HPP
#define SUCCOTASH_LINEAR_LAYOUT_HPP

#include "layout.hpp"
#include "utilities/StringHashTable.hpp"
// TODO: remove above StringHashTable include when will be possible

namespace succotash {

// Dependencies
namespace utilities {
  class Convertible;
}

using utilities::Convertible;
using utilities::StringHashTable;

class LinearLayout : public Layout {
public:
  static LinearLayout* Construct(const StringHashTable<Convertible>& params);

public:
  enum Type {
    Vertical,
    Horizontal,
  };

  LinearLayout(Type orientation);
  void Place(const View* parent_view) override;

private:
  Type orientation_;
};

struct LinearLayoutParams : LayoutParams {
  static LinearLayoutParams* Construct(const StringHashTable<Convertible>& xml_params,
                                       LinearLayoutParams* params = nullptr);

  int weight;
};

} // succotash

#endif // SUCCOTASH_LINEAR_LAYOUT_HPP
