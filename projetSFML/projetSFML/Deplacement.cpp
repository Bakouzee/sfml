#include <SFML/Graphics.hpp>
#include "windows.h"
#include "Arthur.h"
#include <iostream>

void Deplacement(sf::CircleShape &player, sf::Time elapsedTime)
{
	float speed = 200;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		player.setRotation(player.getRotation() + 1 * elapsedTime.asSeconds() * speed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		player.setRotation(player.getRotation() - 1 * elapsedTime.asSeconds() * speed);
	}
}

sf::Vector2f CoordPlayer(sf::CircleShape& player, sf::CircleShape circleGame)
{
	return circleGame.getPosition() + sf::Vector2f(cos(player.getRotation() * (PI / 180)), sin(player.getRotation() * (PI / 180))) * circleRadius;
}