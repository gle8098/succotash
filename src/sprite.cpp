#include "sprite.hpp"

#include "utilities/Convertible.hpp"


namespace succotash {

//------------------------------------------------------------------------------
// Ctors.
//------------------------------------------------------------------------------

Sprite::Sprite() {
  Init();
}

Sprite::Sprite(const Params& params)
    : View(params) {
  Init();

  Params::const_iterator it;
  if ((it = params.find("texture")) != params.end()) {
    LoadTexture(it->second.ToString());
  }
  if ((it = params.find("color")) != params.end()) {
    sprite_.setColor(sf::Color(it->second.ToInt()));
  }
}

Sprite::~Sprite() {
  delete sprite_.getTexture();  // tmp. It must be a TextureManager task.
}

void Sprite::Init() {
}

//------------------------------------------------------------------------------
// Methods.
//------------------------------------------------------------------------------

void Sprite::LoadTexture(const sf::String& file) {
  auto texture = new sf::Texture; // tmp
  if (!texture->loadFromFile(file)) {
    fprintf(stderr, "Error while loading texture\n");
  }
  sprite_.setTexture(*texture);
  UpdateSpriteSize(); // Important, since sprite might had rect_ != 0.
}

void Sprite::DrawSelf(sf::RenderWindow& display) const {
  display.draw(sprite_);
}

void Sprite::MoveBy(const sf::Vector2f& offset) {
  View::MoveBy(offset);
  sprite_.move(offset);
}

void Sprite::Resize(const sf::Vector2f& new_size) {
  View::Resize(new_size);
  UpdateSpriteSize();
}

void Sprite::UpdateSpriteSize() {
  auto new_rect = GetRect();
  if (new_rect.width != 0 && new_rect.height != 0) {
    auto old_rect = sprite_.getGlobalBounds();
    sprite_.scale(
        new_rect.width/old_rect.width, new_rect.height/old_rect.height);
  }
}

} // succotash
