#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "view.hpp"

namespace succotash {

class Sprite : public View {
public:
  Sprite();
  Sprite(const Params& params);
  ~Sprite();

  void LoadTexture(const sf::String& string);

  void DrawSelf(sf::RenderWindow& window) const override;

  void MoveBy(const sf::Vector2f& offset)   override;
  void Resize(const sf::Vector2f& new_size) override;

private:
  void Init();
  void UpdateSpriteSize();

private:
  sf::Sprite sprite_;
};

} // succotash

#endif // SPRITE_HPP

