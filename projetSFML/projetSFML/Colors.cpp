#include "Colors.h"

Colors ChangeColor(Colors& colorsToModify) {
	colorsToModify.primary = sf::Color::Red;
	colorsToModify.secondary = sf::Color::Blue;
	return colorsToModify;
}