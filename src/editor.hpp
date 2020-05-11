#ifndef EDITOR_HPP
#define EDITOR_HPP

#include "view.hpp"

namespace succotash {

class Editor {
public:
  Editor();
  ~Editor() = default;

  void Run();

  const ViewPtr GetMasterView() const;
  ViewPtr GetMasterView();

private:
  void HandleClick(const sf::Event::MouseButtonEvent& mouse_pos);

private:
  ViewPtr master_view_;
  sf::RenderWindow display_;
};

} // succotash

#endif // EDITOR_HPP

