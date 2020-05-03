#include "editor.hpp"
#include "button.hpp"
#include "font_manager.hpp"
#include "linear_layout.hpp"
#include <iostream>
#include "model-parser/ParsingObjects.hpp"

using namespace succotash;

int main0() {
  LoadDefaultFont("font/Arial.ttf");
  xml::InitFactories();

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

  const size_t buttons_cnt = 3;
  Button* buttons[buttons_cnt];
  auto button_context = new View;

  for (size_t i = 0; i < buttons_cnt; ++i) {
    sf::String name = "Button #" + std::to_string(i);
    buttons[i] = new Button(name, button_action);
    button_context->AddSon(buttons[i]);
  }

  LinearLayout layout1(LinearLayout::Type::Vertical);
  // layout1.SetWeights({4, 2, 3});
  buttons->SetLayout(&layout1);

  master_view.AddSon(button_context);

  LinearLayout layout2(LinearLayout::Type::Vertical);
  master_view.SetLayout(&layout2);

  // TODO: memory leak

  editor.Run();

  return 0;
}

