#include <SFML/Graphics.hpp>
#include "windows.h"
#include "AudioManager.h"
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
		PlayHurtSound();
	}
}

sf::ConvexShape lifeCircle()
{
	sf::ConvexShape heart;
	heart.setPointCount(242);
	int o = 0;
	for (float t = 0; t <= 60; t += 0.5f)
	{
		float x = -0.01f * (-pow(t, 2) + 40 * t + 1200) * sin(PI * t / 180);
		float y = 0.01f * (-pow(t, 2) + 40 * t + 1200) * cos(PI * t / 180);

		heart.setPoint(o, sf::Vector2f(x * 3, -y * 3));
		o++;
	}
	for (float t = 60; t >= 0; t -= 0.5f)
	{
		float x = 0.01f * (-pow(t, 2) + 40 * t + 1200) * sin(PI * t / 180);
		float y = 0.01f * (-pow(t, 2) + 40 * t + 1200) * cos(PI * t / 180);

		heart.setPoint(o, sf::Vector2f(x * 3, -y * 3));
		o++;
	}

	float circleLifeRadius = 20;
	heart.setFillColor(sf::Color::Red);
	heart.setOutlineThickness(2);
	heart.setOutlineColor(sf::Color::White);
	return heart;
}

void SetPositionLifeCircle(Player& actualPlayer, float circleLifeRadius, float screenResolutionX)
{
	float posX = 0;
	float offSet = 0;
	float multiplicateur = 0;

	if(actualPlayer.numberPlayer == 1)
	{
		posX = 80;
		offSet = 20;
		multiplicateur = 1;
	}
	else
	{
		posX = screenResolutionX - 80;
		offSet = -20;
		multiplicateur = -1;
	}

	for(int i = 0; i < 3; i++)
	{
		actualPlayer.tabLifeCircle[i].setPosition(posX, 120);
		posX += multiplicateur * circleLifeRadius * 2 + offSet;
	}
}