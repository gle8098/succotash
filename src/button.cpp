#include "button.hpp"

#include <utility>  // std::move

#include "font_manager.hpp"


namespace succotash {

Button::Button(const sf::String& string,
               std::function<void(const Button*)> action)
    : text_(string, GetDefaultFont()),
      action_(std::move(action)) {
  text_.setPosition(shape_.getPosition());
  text_.setFillColor(sf::Color::Black);
  shape_.setFillColor(sf::Color::White);
  shape_.setOutlineColor(sf::Color::Red);
  shape_.setOutlineThickness(3);
}

void Button::DrawSelf(sf::RenderWindow& window) const {
  window.draw(shape_);
  window.draw(text_);
}

bool Button::OnClickEvent(View* clicked_view) const {
  if (action_) {
    action_(this);
    return true;
  }
  return View::OnClickEvent(clicked_view);
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
