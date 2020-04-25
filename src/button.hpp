#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <functional> // std::function

#include "view.hpp"


namespace succotash {

class Button : public View {
public:
  Button(const sf::String& string, std::function<void(const Button*)> action);
  ~Button() = default;

  const sf::String& GetText() const;

  void DrawSelf(sf::RenderWindow& window) const override;
  bool OnClickEvent(View* clicked_view) const override;

private:
  void MoveTo(const sf::Vector2f& new_pos) override;
  void Resize(const sf::Vector2f& new_size) override;

private:
  sf::Text text_;
  std::function<void(const Button*)> action_;
};

} // succotash

#endif // BUTTON_HPP

