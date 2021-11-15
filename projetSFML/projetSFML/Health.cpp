#include <SFML/Graphics.hpp>
#include "windows.h"
#include "Arthur.h"
#include <iostream>

void setLife(Player& actualPlayer, int lifeChange, sf::Clock clockPlayer)
{
	if(lifeChange == 1 && actualPlayer.actualLife != 3)
	{
		actualPlayer.tabLifeCircle[actualPlayer.actualLife].setFillColor(sf::Color(180, 0, 0, 255));
		actualPlayer.actualLife += lifeChange;
	}
	else if(lifeChange == -1 && actualPlayer.actualLife != 0)
	{
		actualPlayer.tabLifeCircle[actualPlayer.actualLife - 1].setFillColor(sf::Color(0, 0, 0, 0));
		actualPlayer.actualLife += lifeChange;
		clockPlayer.restart();
	}
}

sf::CircleShape lifeCircle()
{
	float circleLifeRadius = 20;
	sf::CircleShape newLifeCircle(circleLifeRadius, 100);
	newLifeCircle.setFillColor(sf::Color(180,0,0, 255));
	newLifeCircle.setOutlineThickness(2);
	newLifeCircle.setOutlineColor(sf::Color(255, 255, 255, 255));
	newLifeCircle.setOrigin(circleLifeRadius, circleLifeRadius);
	return newLifeCircle;
}

void SetPositionLifeCircle(Player& actualPlayer, float circleLifeRadius, float screenResolutionX)
{
	float posX = 0;
	float offSet = 0;
	float multiplicateur = 0;

	if(actualPlayer.numberPlayer == 1)
	{
		posX = 50;
		offSet = 20;
		multiplicateur = 1;
	}
	else
	{
		posX = screenResolutionX - 50;
		offSet = -20;
		multiplicateur = -1;
	}

	for(int i = 0; i < 3; i++)
	{
		actualPlayer.tabLifeCircle[i].setPosition(posX, 100);
		posX += multiplicateur * circleLifeRadius * 2 + offSet;
	}
}