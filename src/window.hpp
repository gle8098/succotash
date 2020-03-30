#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "view.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

namespace succotash {

class Window : public sf::RenderWindow {
public:
  Window();

  const View* GetMasterView() const;
  View* GetMasterView();

  void DrawViews();

private:
  View master_view_;
};

}

#endif // WINDOW_HPP

