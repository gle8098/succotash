#ifndef EDITOR_HPP
#define EDITOR_HPP

#include "window.hpp"
#include "view.hpp"


namespace succotash {

class Editor {
public:
  Editor() = default;
  ~Editor() = default;

  Window* GetWindow();
  const Window* GetWindow() const;

  void Run();

private:
  void HandleClick(const sf::Event::MouseButtonEvent& mouse_pos);

private:
  Window window_;
};

} // succotash

#endif // EDITOR_HPP

