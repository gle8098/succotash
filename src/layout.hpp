#ifndef SUCCOTASH_LAYOUT_HPP
#define SUCCOTASH_LAYOUT_HPP

namespace succotash {

class View;


struct Layout {
  virtual void Place(std::vector<View*> view) = 0;
};

} // succotash

#endif // SUCCOTASH_LAYOUT_HPP

