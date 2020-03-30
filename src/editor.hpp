#ifndef EDITOR_HPP
#define EDITOR_HPP


#include "window.hpp"


namespace succotash {

class Editor {
  public:
    Editor();
    ~Editor();

    // Setters.
    void SetResolution(size_t width, size_t height);

    void Run();

  private:
    Window window_;
    Tool current_tool_;
};

} // succotash

#endif // EDITOR_HPP

