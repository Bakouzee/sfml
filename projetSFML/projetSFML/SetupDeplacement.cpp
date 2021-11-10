#include <SFML/Graphics.hpp>
#include "windows.h"
#include "Arthur.h"
#include <iostream>

sf::CircleShape CircleGameCrea(float positionX, float positionY)
{
	sf::CircleShape circleGame(circleRadius, 100);
	circleGame.setFillColor(sf::Color(0, 0, 0, 0));
	circleGame.setOutlineThickness(5);
	circleGame.setOutlineColor(sf::Color(0, 0, 250, 255));
	circleGame.setPosition(positionX, positionY);
	circleGame.setOrigin(circleRadius, circleRadius);
	return circleGame;
}

sf::CircleShape PlayerCrea(sf::CircleShape circleGame)
{
	sf::CircleShape newPlayer(playerRadius, 3);
	newPlayer.setFillColor(sf::Color(150, 0, 0));
	newPlayer.setPosition(circleGame.getPosition());
	newPlayer.setOrigin(playerRadius / 2, (playerRadius / 2) - circleRadius);
	return newPlayer;
}

sf::CircleShape BonusCrea(sf::CircleShape circleGame)
{
	sf::CircleShape newBonus(playerRadius, 4);
	newBonus.setFillColor(sf::Color(150, 0, 0));
	newBonus.setPosition(circleGame.getPosition());
	newBonus.setOrigin(playerRadius, playerRadius + circleRadius);
	return newBonus;
}