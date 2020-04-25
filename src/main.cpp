#include "editor.hpp"
#include "button.hpp"
#include "font_manager.hpp"
#include "linear_layout.hpp"
#include <iostream>

int main() {
  LoadDefaultFont("Arial.ttf");

  succotash::Editor editor;

  // Setup testing layout
  succotash::View& master_view = editor.GetMasterView();

  auto button_action = [](const succotash::Button* button) {
      std::cout << button->GetText().toAnsiString() << std::endl;
    };
  auto button1 = new succotash::Button("Button #1", button_action);
  auto button2 = new succotash::Button("Button #2", button_action);
  master_view.AddSon(button1);
  master_view.AddSon(button2);

  master_view.SetLayout(new succotash::LinearLayout(true));
  // TODO: memory leak

  editor.Run();

  return 0;
}

