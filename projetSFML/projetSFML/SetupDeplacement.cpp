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

Player NewPlayer(sf::CircleShape shape, int life, int number)
{
	Player newPlayer;
	newPlayer.player = shape;
	newPlayer.actualLife = life;
	newPlayer.numberPlayer = number;
	for(int i = 0; i < 3; i++)
	{
		newPlayer.tabLifeCircle[i] = lifeCircle();
	}
	return newPlayer;
}