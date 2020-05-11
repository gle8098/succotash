#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <functional> // std::function

#include "view.hpp"


namespace succotash {

class Button;
using ButtonPtr = std::shared_ptr<Button>;


class Button : public View {
public:
  Button(const sf::String& string);
  Button(const sf::String& string, std::function<void(const ButtonPtr)> action);
  Button(const Params& params);
  ~Button() = default;

  void SetAction(std::function<void(const ButtonPtr)> action);
  const sf::String& GetText() const;

  void DrawSelf(sf::RenderWindow& window) const override;
  void OnClickEvent(ViewPtr clicked_view)         override;

  void MoveTo(const sf::Vector2f& new_pos)  override;
  void Resize(const sf::Vector2f& new_size) override;

  // Used to solve a problem of base initializer and a delegation in
  // Button(const Params& params);
  void Init(const sf::String& string);

private:
  sf::Text text_;
  std::function<void(const ButtonPtr)> action_;
};

} // succotash

#endif // BUTTON_HPP

