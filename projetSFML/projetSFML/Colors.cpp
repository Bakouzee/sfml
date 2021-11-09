#include <iostream>
#include "Colors.h"

//Mettre une condition dans le main pour savoir quand le score est égale à certains pourcentage ou autre, on change la couleur pour tous
void ChangeColorForEverything(Colors& colorsPlayer, Colors& colorsEntities, ColorID& colorApplied) {
	// tous les multiples de 10 en score => nouvelle couleur !
	int randomColor = 0;
	randomColor = rand() % 6 + 1;
	while (randomColor % 2 == 0 || randomColor == colorApplied) {
		randomColor = rand() % 6 + 1;
		std::cout << "Nope!" << std::endl;
	}
	std::cout << "Yes!" << std::endl;
	std::cout << randomColor << std::endl;


	// On applique la nouvelle couleur
	switch (randomColor) {
	case 1:
		colorsPlayer.primary = sf::Color::Black;
		colorsPlayer.secondary = sf::Color::White;
		colorsEntities.primary = sf::Color::Black;
		colorsEntities.secondary = sf::Color::White;
		colorApplied = ColorID::BLACK;
		break;
	case 2:
		colorsPlayer.primary = sf::Color::White;
		colorsPlayer.secondary = sf::Color::Black;
		colorsEntities.primary = sf::Color::White;
		colorsEntities.secondary = sf::Color::Black;
		colorApplied = ColorID::WHITE;
		break;
	case 3:
		colorsPlayer.primary = sf::Color::Green;
		colorsPlayer.secondary = sf::Color::Red;
		colorsEntities.primary = sf::Color::Green;
		colorsEntities.secondary = sf::Color::Red;
		colorApplied = ColorID::GREEN;
		break;
	case 4:
		colorsPlayer.primary = sf::Color::Red;
		colorsPlayer.secondary = sf::Color::Green;
		colorsEntities.primary = sf::Color::Red;
		colorsEntities.secondary = sf::Color::Green;
		colorApplied = ColorID::RED;
		break;
	case 5:
		colorsPlayer.primary = sf::Color::Yellow;
		colorsPlayer.secondary = sf::Color::Blue;
		colorsEntities.primary = sf::Color::Yellow;
		colorsEntities.secondary = sf::Color::Blue;
		colorApplied = ColorID::YELLOW;
		break;
	case 6:
		colorsPlayer.primary = sf::Color::Blue;
		colorsPlayer.secondary = sf::Color::Yellow;
		colorsEntities.primary = sf::Color::Blue;
		colorsEntities.secondary = sf::Color::Yellow;
		colorApplied = ColorID::BLUE;
		break;
	default:
		break;
	}
}

//La fonction est utilisée pour changer la couleur du joueur en exécutant un input (E par exemple) --> à mettre dans les events
Colors ChangeSide(Colors colorsPlayer) {
	Colors colorSwap = { colorsPlayer.primary, colorsPlayer.secondary };
	colorsPlayer.primary = colorSwap.secondary;
	colorsPlayer.secondary = colorSwap.primary;
	return colorsPlayer;
}