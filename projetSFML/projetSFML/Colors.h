#pragma once
#include <SFML/Graphics.hpp>

struct Colors {
	sf::Color primary = sf::Color::Black;
	sf::Color secondary = sf::Color::White;
};

Colors ChangeColor(Colors& colorsToModify);