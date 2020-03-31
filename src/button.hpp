#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>

#include "view.hpp"


namespace succotash {

class Button : public View {
public:
  explicit Button(const sf::String& string);

  void DrawSelf(sf::RenderWindow& window) const override;

  const sf::String& GetText() const;
  void SetAction(std::function<void(const Button*)>);

  bool OnClickEvent(View* clicked_view) const override;

private:
  sf::Text text_;
  std::function<void(const Button*)> action_;
};

} // succotash

#endif // BUTTON_HPP

