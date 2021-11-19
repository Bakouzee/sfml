#pragma once
#include <SFML/Graphics.hpp>
#include "Arthur.h"

enum Bonus {
	SLOW_DOWN,
	HEALTH_UP
};

sf::CircleShape BonusCrea1J(sf::CircleShape& player1, sf::CircleShape circleGame);
sf::CircleShape BonusCrea2J(sf::CircleShape player1, sf::CircleShape player2, sf::CircleShape circleGame);
void SetupPositionBonus2J(sf::CircleShape& bonus, sf::CircleShape& player1, sf::CircleShape& player2);
void ChooseBonus(sf::CircleShape& bonus, Player& player1, Player& player2, bool isPlayerTwo, bool& showBonus, sf::Clock& timerBonus);
void CollideAndApplyBonus(sf::CircleShape& bonus, Player& player1, Player& player2, bool isPlayerTwo, bool& showBonus, sf::Clock& timerBonus);
void SpeedDownForSeconds(Player& playerAdversary, bool& showBonus);