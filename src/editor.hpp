#ifndef EDITOR_HPP
#define EDITOR_HPP

#include "window.hpp"
#include "view.hpp"


namespace succotash {

class Editor {
public:
  Editor();
  ~Editor() = default;

  // Setters.
  void SetResolution(size_t width, size_t height);

  void Run();

private:
  void HandleClick(const sf::Vector2i& mouse_pos);

private:
  Window window_;
};

} // succotash

#endif // EDITOR_HPP

