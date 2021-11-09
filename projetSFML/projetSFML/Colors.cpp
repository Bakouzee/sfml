#include <iostream>
#include "Colors.h"

//Mettre une condition dans le main pour savoir quand le score est égale à certains pourcentage ou autre, on change la couleur pour tous
Colors ChangeColorForEverything(Colors& colorsToModify, ColorID& colorApplied) {
	// tous les multiples de 10 en score => nouvelle couleur !
	int randomColor = 0;
	randomColor = rand() + 1 % 6 + 1;
	while (randomColor % 2 != 0 && randomColor != colorApplied) {
		randomColor = rand() + 1 % 6 + 1;
	}
	// On applique la nouvelle couleur
	switch (randomColor) {
	case 1:
		colorsToModify.primary = sf::Color::Black;
		colorsToModify.secondary = sf::Color::White;
		colorApplied = ColorID::BLACK;
		break;
	case 2:
		colorsToModify.primary = sf::Color::White;
		colorsToModify.secondary = sf::Color::Black;
		colorApplied = ColorID::WHITE;
		break;
	case 3:
		colorsToModify.primary = sf::Color::Green;
		colorsToModify.secondary = sf::Color::Red;
		colorApplied = ColorID::GREEN;
		break;
	case 4:
		colorsToModify.primary = sf::Color::Red;
		colorsToModify.secondary = sf::Color::Green;
		colorApplied = ColorID::RED;
		break;
	case 5:
		colorsToModify.primary = sf::Color::Yellow;
		colorsToModify.secondary = sf::Color::Blue;
		colorApplied = ColorID::YELLOW;
		break;
	case 6:
		colorsToModify.primary = sf::Color::Blue;
		colorsToModify.secondary = sf::Color::Yellow;
		colorApplied = ColorID::BLUE;
		break;
	default:
		break;
	}
	return colorsToModify;
}

//La fonction est utilisée pour changer la couleur du joueur en exécutant un input (E par exemple) --> à mettre dans les events
Colors ChangeSide(Colors colorsPlayer) {
	Colors colorSwap = { colorsPlayer.primary, colorsPlayer.secondary };
	colorsPlayer.primary = colorSwap.secondary;
	colorsPlayer.secondary = colorSwap.primary;
	return colorsPlayer;
}