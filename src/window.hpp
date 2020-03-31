#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "view.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

namespace succotash {

class Window : public sf::RenderWindow {
public:
  Window(unsigned int width = 800, unsigned int height = 600);

  const View* GetMasterView() const;
  View* GetMasterView();

  void DrawViews();

  void UpdateWindowSize();

private:
  View master_view_;
};

}

#endif // WINDOW_HPP

