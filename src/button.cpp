#include "button.hpp"

#include <utility>  // std::move

#include "font_manager.hpp"


namespace succotash {

Button::Button(const sf::String& string)
    : text_(string, GetDefaultFont()),
      action_() {

  text_.setFillColor(sf::Color::Black);
  shape_.setFillColor(sf::Color::White);
  shape_.setOutlineColor(sf::Color::Red);
  shape_.setOutlineThickness(3);
}

Button::Button(const sf::String& string,
               std::function<void(const Button*)> action)
    : Button(string) {

  SetAction(action);
}

void Button::SetAction(std::function<void(const Button*)> action) {
  action_ = std::move(action);
}

void Button::DrawSelf(sf::RenderWindow& display) const {
  display.draw(shape_);
  display.draw(text_);
}

void Button::OnClickEvent(View* clicked_view) {
  if (action_) {
    action_(this);
  }
}

const sf::String& Button::GetText() const {
  return text_.getString();
}

void Button::MoveTo(const sf::Vector2f& new_pos) {
  View::MoveTo(new_pos);
  text_.setPosition(shape_.getPosition());
}

void Button::Resize(const sf::Vector2f& new_size) {
  View::Resize(new_size);
  //text_.setSize(shape_.getSize());
}

} // succotash
