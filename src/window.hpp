#ifndef WINDOW_HPP
#define WINDOW_HPP


#include "view.hpp"


class Window : sf::RenderWindow {
  public:
    Window();

    bool HandleClick(const sf::Vector2i& click_pos);
    void DrawViews();

  private:
    View master_view_;
};


#endif // WINDOW_HPP

