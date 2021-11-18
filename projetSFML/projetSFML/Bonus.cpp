#include "Bonus.h"

sf::CircleShape BonusCrea1J(sf::CircleShape player1, sf::CircleShape circleGame) {
	sf::CircleShape newBonus(playerRadius, 4);
	newBonus.setPosition(circleGame.getPosition());
	newBonus.setOrigin(playerRadius, playerRadius + circleRadius);
	newBonus.setRotation(player1.getRotation() + 360);
	return newBonus;
}

sf::CircleShape BonusCrea2J(sf::CircleShape player1, sf::CircleShape player2, sf::CircleShape circleGame)
{
	sf::CircleShape newBonus(playerRadius, 4);
	newBonus.setPosition(circleGame.getPosition());
	newBonus.setOrigin(playerRadius, playerRadius + circleRadius);
	return newBonus;
}

void SetupPositionBonus2J(sf::CircleShape& bonus, sf::CircleShape& player1, sf::CircleShape& player2) {
	float distancePlayers = (player1.getRotation() + player2.getRotation()) / 2;
	if (distancePlayers <= 180.f) {
		bonus.setRotation(distancePlayers - 180.f);
	}
	else {
		bonus.setRotation(distancePlayers + 180.f);
	}
}

void ChooseBonus(sf::CircleShape& bonus, Player& player1, Player& player2, bool isPlayerTwo, bool& showBonus, sf::Clock& timerBonus) {
	
	int randBonus = rand() % 2 + 1;
	switch (randBonus) {
	case 1:
		bonus.setFillColor(sf::Color::Red); // health up		
		break;
	case 2:
		bonus.setFillColor(sf::Color::Cyan); // slow down the adversary
		break;
	default:
		break;
	}
	timerBonus.restart();
	showBonus = true;
	if (bonus.getFillColor() == sf::Color::Red) {
		float rotationBonusMin = bonus.getRotation() - 5;
		float rotationBonusMax = bonus.getRotation() + 5;
		if (player1.player.getRotation() <= 180) {
			if (player1.player.getRotation() + 180 <= rotationBonusMax && player1.player.getRotation() + 180 >= rotationBonusMin) {
				setLife(player1, 1, timerBonus);
				showBonus = false;
			}
		}
		else {
			if (player1.player.getRotation() - 180 <= rotationBonusMax && player1.player.getRotation() - 180 >= rotationBonusMin) {
				setLife(player1, 1, timerBonus);
				showBonus = false;
			}
		}

		if (player2.player.getRotation() <= 180 && isPlayerTwo) {
			if (player2.player.getRotation() + 180 <= rotationBonusMax && player2.player.getRotation() + 180 >= rotationBonusMin) {
				setLife(player2, 1, timerBonus);
				showBonus = false;
			}
		}
		else {
			if (isPlayerTwo && player2.player.getRotation() - 180 <= rotationBonusMax && player2.player.getRotation() - 180 >= rotationBonusMin) {
				setLife(player2, 1, timerBonus);
				showBonus = false;
			}
		}
	}
}
