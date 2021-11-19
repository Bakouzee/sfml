#include <SFML/Graphics.hpp>
#include "windows.h"
#include "Arthur.h"
#include <iostream>

void Deplacement(Player& actualPlayer, sf::Time elapsedTime)
{
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && actualPlayer.numberPlayer == 2) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && actualPlayer.numberPlayer == 1))
	{
		actualPlayer.player.setRotation(actualPlayer.player.getRotation() + 1 * elapsedTime.asSeconds() * actualPlayer.speedPlayer);
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && actualPlayer.numberPlayer == 2 || (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && actualPlayer.numberPlayer == 1))
	{
		actualPlayer.player.setRotation(actualPlayer.player.getRotation() - 1 * elapsedTime.asSeconds() * actualPlayer.speedPlayer);
	}
}

sf::Vector2f CoordPlayer(sf::CircleShape& player, sf::CircleShape circleGame)
{
	return circleGame.getPosition() + sf::Vector2f(-sin(player.getRotation() * (PI / 180)), cos(player.getRotation() * (PI / 180))) * circleRadius;
}