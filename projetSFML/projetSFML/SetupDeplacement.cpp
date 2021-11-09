#include <SFML/Graphics.hpp>
#include "windows.h"
#include "Arthur.h"
#include <iostream>

sf::CircleShape CircleGameCrea(float positionX, float positionY)
{
	sf::CircleShape circleGame;
	circleGame.setRadius(circleRadius); //RAYON du cercle
	circleGame.setFillColor(sf::Color(0, 0, 0, 0));
	circleGame.setOutlineThickness(5);
	circleGame.setOutlineColor(sf::Color(0, 0, 250, 255));
	circleGame.setPosition(positionX, positionY);
	circleGame.setOrigin(circleRadius, circleRadius);
	return circleGame;
}

sf::CircleShape PlayerCrea(float radius, sf::CircleShape circleGame)
{
	sf::CircleShape newPlayer(radius, 3);
	newPlayer.setFillColor(sf::Color(150, 0, 0));
	newPlayer.setPosition(circleGame.getPosition());
	newPlayer.setOrigin(radius / 2, (radius / 2) - circleRadius);
	return newPlayer;
}