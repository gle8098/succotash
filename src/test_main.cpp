#include "button.hpp"
#include "editor.hpp"
#include "font_manager.hpp"
#include <iostream>
#include "linear_layout.hpp"
#include "model-parser/ModelParser.hpp"
#include "model-parser/ParsingObjects.hpp"

using namespace succotash;

int main() {
  LoadDefaultFont("font/Arial.ttf");
  xml::InitFactories();

  auto button_action = [](const Button* button) {
    std::cout << button->GetText().toAnsiString() <<  " pos: " <<
              int(button->GetShape().getPosition().x) << "," <<
              int(button->GetShape().getPosition().y) << " size: " <<
              int(button->GetShape().getSize().x) << "," <<
              int(button->GetShape().getSize().y) << std::endl;
  };

  View* view = xml::ParseModel("models/test_window.xml");
  int search_ids[] = {1, 2, 3};
  for (int id : search_ids) {
    dynamic_cast<Button*>(view->FindViewById(id))->SetAction(button_action);
  }

  Editor editor;
  editor.GetMasterView()->AddSon(view);

  editor.GetMasterView()->SetLayout(
      CreatePtr<LinearLayout>(LinearLayout::Type::Vertical));

  editor.Run();
}
