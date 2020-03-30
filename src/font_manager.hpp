#ifndef FONT_MANAGER_HPP
#define FONT_MANAGER_HPP

#include <SFML/Graphics.hpp>


static sf::Font font_;

void LoadFont(const std::string& file);
sf::Font GetFont();

#endif // FONT_MANAGER_HPP

