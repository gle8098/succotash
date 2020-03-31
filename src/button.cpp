#include "button.hpp"

#include <utility>
#include "font_manager.hpp"

namespace succotash {

Button::Button(const sf::String& string)
    : text_(string, GetDefaultFont()) {
  text_.setPosition(shape_.getPosition());
  text_.setFillColor(sf::Color::Black);
  shape_.setFillColor(sf::Color::White);
  shape_.setOutlineColor(sf::Color::Red);
  shape_.setOutlineThickness(3);
}


void Button::DrawSelf(sf::RenderWindow& window) const {
  Button* non_const_this = const_cast<Button*>(this);
  non_const_this->text_.setPosition(shape_.getPosition());

  window.draw(shape_);
  window.draw(text_);
}

bool Button::OnClickEvent(View *clicked_view) const {
  if (action_) {
    action_(this);
    return true;
  }
  return View::OnClickEvent(clicked_view);
}

void Button::SetAction(std::function<void(const Button*)> action) {
  action_ = std::move(action);
}

const sf::String& Button::GetText() const {
  return text_.getString();
}

} // succotash
