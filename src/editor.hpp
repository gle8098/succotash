#ifndef EDITOR_HPP
#define EDITOR_HPP

#include "view.hpp"

namespace succotash {

class Editor {
public:
  Editor();
  ~Editor() = default;

  void Run();

  const View* GetMasterView() const;
  View*       GetMasterView();

private:
  void HandleClick(const sf::Event::MouseButtonEvent& mouse_pos);

private:
  View master_view_;
  sf::RenderWindow display_;
};

} // succotash

#endif // EDITOR_HPP

