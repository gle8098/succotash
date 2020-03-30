#ifndef GRID_LAYOUT_HPP
#define GRID_LAYOUT_HPP

#include "layout.hpp"


struct GridLayout : Layout {

  int w_indent_;
  int w_count_;
  int h_indent_;
  int h_count_;

  void Place(const View* parent) override;

private:

  void PlaceLinear();
};


#endif // GRID_LAYOUT_HPP

