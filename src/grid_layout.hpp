#ifndef GRID_LAYOUT_HPP
#define GRID_LAYOUT_HPP

#include "layout.hpp"


class GridLayout {
public:
  int w_indent_;
  int w_count_;
  int h_indent_;
  int h_count_;

public:
  void Place(std::vector<View*> view) override;
};


#endif // GRID_LAYOUT_HPP

