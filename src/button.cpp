#include "button.hpp"

#include <utility>  // std::move

#include "font_manager.hpp"
#include "utilities/Convertible.hpp"


namespace succotash {

//------------------------------------------------------------------------------
// Ctors.
//------------------------------------------------------------------------------

Button::Button() {
  Init();
}

Button::Button(const Params& params)
    : View(params) {
  Init();

  Params::const_iterator it;
  if ((it = params.find("name")) != params.end()) {
    SetString(it->second.ToString());
  }

  if ((it = params.find("color")) != params.end()) {
    shape_.setFillColor(sf::Color(it->second.ToInt()));
  }
}

Button::Button(const sf::String& string) {
  Init();
  SetString(string);
}

Button::Button(const sf::String& string,
               std::function<void(const Button*)> action)
    : Button(string) {
  SetAction(action);
}

void Button::Init() {
  text_.setFont(GetDefaultFont());
  text_.setFillColor(sf::Color::Black);

  shape_.setFillColor(sf::Color::White);
  shape_.setOutlineColor(sf::Color::Red);
  shape_.setOutlineThickness(2);
}

//------------------------------------------------------------------------------
// Methods.
//------------------------------------------------------------------------------

void Button::SetAction(std::function<void(const Button*)> action) {
  action_ = std::move(action);
}

void Button::SetString(const sf::String& string) {
  text_.setString(string);
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
