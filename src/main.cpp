#include "editor.hpp"


int main() {
  succotash::Editor editor;
  // Configure editor.
  editor.SetResolution(1600, 360);

  editor.Run();

  return 0;
}


