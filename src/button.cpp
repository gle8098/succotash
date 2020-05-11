#include "button.hpp"

#include <utility>  // std::move

#include "font_manager.hpp"
#include "utilities/Convertible.hpp"


namespace succotash {

//------------------------------------------------------------------------------
// Ctors.
//------------------------------------------------------------------------------

Button::Button(const Params& params)
    : View(params) {

  Init(params.at("name").ToString());
}

Button::Button(const sf::String& string) {
  Init(string);
}

Button::Button(const sf::String& string,
               std::function<void(const ButtonPtr)> action) {
  Init(string);
  SetAction(action);
}

//------------------------------------------------------------------------------
// Methods.
//------------------------------------------------------------------------------

void Button::Init(const sf::String& string) {
  text_.setString(string);
  text_.setFont(GetDefaultFont());
  text_.setFillColor(sf::Color::Black);

  shape_.setFillColor(sf::Color::White);
  shape_.setOutlineColor(sf::Color::Red);
  shape_.setOutlineThickness(3);
}

void Button::SetAction(std::function<void(const ButtonPtr)> action) {
  action_ = std::move(action);
}

void Button::DrawSelf(sf::RenderWindow& display) const {
  display.draw(shape_);
  display.draw(text_);
}

void Button::OnClickEvent(ViewPtr clicked_view) {
  if (action_) {
    action_(shared_from_base<Button>());
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
