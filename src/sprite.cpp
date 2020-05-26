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
    shape_.setFillColor(sf::Color(it->second.ToInt()));
  }
}

Sprite::~Sprite() {
  delete shape_.getTexture();  // tmp. It must be a TextureManager task.
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
  shape_.setTexture(texture);
  UpdateSpriteSize(); // Important, since sprite might had rect_ != 0.
}

void Sprite::DrawSelf(sf::RenderWindow& display) const {
  display.draw(shape_);
}

void Sprite::MoveBy(const sf::Vector2f& offset) {
  View::MoveBy(offset);
  shape_.move(offset);
}

void Sprite::Resize(const sf::Vector2f& new_size) {
  View::Resize(new_size);
  UpdateSpriteSize();
}

void Sprite::UpdateSpriteSize() {
  auto rect = GetRect();
  if (rect.width != 0 && rect.height != 0) {
    shape_.setPosition(rect.left, rect.top);
    shape_.setSize(sf::Vector2f(rect.width, rect.height));
  }
}

} // succotash
