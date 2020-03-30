#include "font_manager.hpp"


void LoadFont(const std::string& file) {
  font_.loadFromFile(file);
}

sf::Font GetFont() {
  return font_;
}

