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
    : Sprite(params) {
  Init();

  Params::const_iterator it;
  if ((it = params.find("name")) != params.end()) {
    SetString(it->second.ToString());
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

//void Button::DrawSelf(sf::RenderWindow& display) const {
//  //display.draw(text_);
//}

void Button::OnClickEvent(View* clicked_view) {
  if (action_) {
    action_(this);
  }
}

const sf::String& Button::GetText() const {
  return text_.getString();
}

void Button::MoveBy(const sf::Vector2f& offset) {
  Sprite::MoveBy(offset);
  //text_.move(offset);
}

void Button::Resize(const sf::Vector2f& new_size) {
  Sprite::Resize(new_size);
  //text_.setSize(sprite_.getSize());
}

} // succotash
