#include "editor.hpp"
#include "font_manager.hpp"


int main() {
  LoadFont("arial.ttf");
  succotash::Editor editor;
  // Configure editor.
  editor.SetResolution(1600, 360);

  editor.Run();

  return 0;
}

