#include "Bonus.h"

void ChooseBonus(Player& playerCollide, sf::CircleShape& bonus, bool& showBonus, sf::Clock& timerBonus) {

	int randBonus = rand() % 2 + 1;
	switch (randBonus) {
	case 1:
		bonus.setFillColor(sf::Color::Red); // health up
		setLife(playerCollide, 1, timerBonus);
		break;
	case 2:
		bonus.setFillColor(sf::Color::Cyan); // slow down
		break;
	default:
		break;
	}
	timerBonus.restart();
	showBonus = true;
}