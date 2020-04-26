#include "editor.hpp"
#include "button.hpp"
#include "font_manager.hpp"
#include "linear_layout.hpp"
#include <iostream>

using namespace succotash;

int main() {
  LoadDefaultFont("Arial.ttf");

  Editor editor;

  // Setup testing layout
  View& master_view = editor.GetMasterView();

  auto button_action = [](const Button* button) {
      std::cout << button->GetText().toAnsiString() <<  " pos: " <<
                   int(button->GetShape().getPosition().x) << "," <<
                   int(button->GetShape().getPosition().y) << " size: " <<
                   int(button->GetShape().getSize().x) << "," <<
                   int(button->GetShape().getSize().y) << std::endl;
    };
  auto button1 = new Button("Button #1", button_action);
  auto button2 = new Button("Button #2", button_action);
  auto button3 = new Button("Button #3", button_action);

  auto buttons = new View;
  buttons->AddSon(button1);
  buttons->AddSon(button2);
  buttons->AddSon(button3);

  LinearLayout layout1(LinearLayout::Type::Vertical);
  layout1.SetWeights({4, 2, 3});
  buttons->SetLayout(&layout1);

  master_view.AddSon(buttons);

  LinearLayout layout2(LinearLayout::Type::Vertical);
  master_view.SetLayout(&layout2);

  // TODO: memory leak

  editor.Run();

  return 0;
}

