#include "button.hpp"
#include "editor.hpp"
#include "font_manager.hpp"
#include "linear_layout.hpp"
#include <iostream>

int main() {
  LoadDefaultFont("Arial.ttf");
  succotash::Editor editor;

  // Setup testing layout
  succotash::View* master_view = editor.GetWindow()->GetMasterView();
  master_view->AddSon(new succotash::Button("Button #1"));
  master_view->AddSon(new succotash::Button("Button #2"));
  for (succotash::View* son : master_view->GetSons()) {
    ((succotash::Button*) son)->SetAction([](const succotash::Button* button) {
      std::cout << button->GetText().toAnsiString() << std::endl;
    });
  }
  master_view->SetLayout(new succotash::LinearLayout(true));
  // TODO: memory leak

  editor.Run();
  return 0;
}

