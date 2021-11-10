#pragma once
#include <SFML/Graphics.hpp>

struct Colors {
	sf::Color primary = sf::Color::Black;
	sf::Color secondary = sf::Color::White;
};

//Initialiser la couleur ID en BLACK pour le début de la partie
enum ColorID {
	BLACK = 1,
    WHITE = 2,
	GREEN = 3,
	RED = 4,
	YELLOW = 5,
	BLUE = 6,
};

void ChangeColorForEverything(Colors& colorsPlayer, Colors& colorsEntities, ColorID& colorToApply);
Colors ChangeSide(Colors colorsPlayer);