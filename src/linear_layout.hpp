#ifndef SUCCOTASH_LINEAR_LAYOUT_HPP
#define SUCCOTASH_LINEAR_LAYOUT_HPP

#include "layout.hpp"
#include <vector>

namespace succotash {

class LinearLayout : public Layout {
public:
  enum Type {
    Vertical,
    Horizontal,
  };

  LinearLayout(Type orientation);

  void SetWeights(std::vector<int>&  weights);
  void SetWeights(std::vector<int>&& weights);
  void Place(const View* parent_view) override;

private:
  Type orientation_;
  std::vector<int> weights_;
};

} // succotash

#endif // SUCCOTASH_LINEAR_LAYOUT_HPP
