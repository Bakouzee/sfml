#include "Bonus.h"
#include <iostream>

sf::CircleShape BonusCrea1J(sf::CircleShape& player1, sf::CircleShape circleGame) {
	sf::CircleShape newBonus(playerRadius, 4);
	newBonus.setPosition(circleGame.getPosition());
	newBonus.setOrigin(playerRadius, playerRadius - circleRadius);
	if (player1.getRotation() <= 180) {
		newBonus.setRotation(player1.getRotation() + 180);
	}
	else {
		newBonus.setRotation(player1.getRotation() - 180);
	}
	return newBonus;
}

sf::CircleShape BonusCrea2J(sf::CircleShape player1, sf::CircleShape player2, sf::CircleShape circleGame)
{
	sf::CircleShape newBonus(playerRadius, 4);
	newBonus.setPosition(circleGame.getPosition());
	newBonus.setOrigin(playerRadius, playerRadius - circleRadius);
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
}

void CollideAndApplyBonus(sf::CircleShape& bonus, Player& player1, Player& player2, bool isPlayerTwo, bool& showBonus, sf::Clock& timerBonus) {
	float rotationBonusMin = bonus.getRotation() - 5;
	float rotationBonusMax = bonus.getRotation() + 5;
	if (bonus.getFillColor() == sf::Color::Red && !isPlayerTwo) {
		if (player1.player.getRotation() <= 180) {
			if (player1.player.getRotation() <= rotationBonusMax && player1.player.getRotation() >= rotationBonusMin) {
				setLife(player1, 1, timerBonus);
				showBonus = false;
			}
		}
		else {
			if (player1.player.getRotation() <= rotationBonusMax && player1.player.getRotation() >= rotationBonusMin) {
				setLife(player1, 1, timerBonus);
				showBonus = false;
			}
		}
	}
	if (bonus.getFillColor() == sf::Color::Cyan && !isPlayerTwo) {
		if (player1.player.getRotation() <= 180) {
			if (player1.player.getRotation() <= rotationBonusMax && player1.player.getRotation() >= rotationBonusMin) {
				SpeedDownForSeconds(player2, showBonus);
			}
		}
		else {
			if (player1.player.getRotation() <= rotationBonusMax && player1.player.getRotation() >= rotationBonusMin) {
				SpeedDownForSeconds(player2, showBonus);
			}
		}
	}

	if (bonus.getFillColor() == sf::Color::Red && isPlayerTwo) {
		if (player1.player.getRotation() <= 180) {
			if (player1.player.getRotation() <= rotationBonusMax && player1.player.getRotation() >= rotationBonusMin) {
				setLife(player1, 1, timerBonus);
				showBonus = false;
			}
		}
		else {
			if (player1.player.getRotation() <= rotationBonusMax && player1.player.getRotation() >= rotationBonusMin) {
				setLife(player1, 1, timerBonus);
				showBonus = false;
			}
		}

		if (player2.player.getRotation() <= 180) {
			if (player2.player.getRotation() <= rotationBonusMax && player2.player.getRotation()  >= rotationBonusMin) {
				setLife(player2, 1, timerBonus);
				showBonus = false;
			}
		}
		else {
			if (player2.player.getRotation()  <= rotationBonusMax && player2.player.getRotation() >= rotationBonusMin) {
				setLife(player2, 1, timerBonus);
				showBonus = false;
			}
		}
	}
	if (bonus.getFillColor() == sf::Color::Cyan && isPlayerTwo) {
		if (player1.player.getRotation() <= 180) {
			if (player1.player.getRotation() <= rotationBonusMax && player1.player.getRotation() >= rotationBonusMin) {
				SpeedDownForSeconds(player2, showBonus);
			}
		}
		else {
			if (player1.player.getRotation() <= rotationBonusMax && player1.player.getRotation() >= rotationBonusMin) {
				SpeedDownForSeconds(player2, showBonus);
			}
		}

		if (player2.player.getRotation() <= 180) {
			if (player2.player.getRotation()  <= rotationBonusMax && player2.player.getRotation()  >= rotationBonusMin) {
				SpeedDownForSeconds(player1, showBonus);
			}
		}
		else {
			if (player2.player.getRotation()  <= rotationBonusMax && player2.player.getRotation()  >= rotationBonusMin) {
				SpeedDownForSeconds(player1, showBonus);
			}
		}
	}


}

void SpeedDownForSeconds(Player& playerAdversary, bool& showBonus) {
	showBonus = false;
	sf::Clock* timerSlowD = new sf::Clock;
	timerSlowD->restart();
	playerAdversary.speedPlayer = 75.f;
	if (timerSlowD->getElapsedTime().asSeconds() >= 1.5f) {
		playerAdversary.speedPlayer = 100.f;
		delete timerSlowD;
	}
}