#ifndef SUCCOTASH_GRID_LAYOUT_HPP
#define SUCCOTASH_GRID_LAYOUT_HPP

#include <SFML/Graphics.hpp>


namespace succotash {

class View;

struct Layout {
  virtual void Place(std::vector<View*>& views,
                     const sf::RectangleShape& area) = 0;
};

} // succotash

#endif // SUCCOTASH_GRID_LAYOUT_HPP
