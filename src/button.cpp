#include "button.hpp"
#include "font_manager.hpp"


Button::Button(const sf::Text& string) {
    : text_(string, GetFont()) {
  text_.setPosition(shape_->getPosition());
  shape_->setFillColor(sf::Color::White);
}

Result<View*> Button::InvokeHandler() {
  return Result(false, );
}

void Button::DrawSelf(sf::RenderWindow& window) const {
  window.draw(text_);
  window.draw(*this);
}

//bool Button::HandleClick(const sf::Vector2i& pos) const {
//
//}


