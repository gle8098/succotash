#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>

#include "view.hpp"


namespace succotash {

class Button : public View {
public:
  Button(const sf::Text& string);

  void DrawSelf() const override;

  void SetAction();

private:
  sf::Text text_;
  std::function<void()> action_ = [](){};
};

} // succotash

#endif // BUTTON_HPP

