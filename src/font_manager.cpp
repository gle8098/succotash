#include "font_manager.hpp"

static sf::Font default_font;

void LoadDefaultFont(const std::string& file) {
  default_font.loadFromFile(file);
}

const sf::Font& GetDefaultFont() {
  return default_font;
}

