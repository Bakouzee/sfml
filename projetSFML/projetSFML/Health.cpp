#include <SFML/Graphics.hpp>
#include "windows.h"
#include "Arthur.h"
#include <iostream>

int setLife(int actualLife, int lifeChange, sf::CircleShape tabLifeCircle[])
{
	if(actualLife != 3 && lifeChange >= 1)
	{
		if(lifeChange == 1)
		{
			std::cout << "JE GAGNE DE LA VIE";
			tabLifeCircle[actualLife - 1].setFillColor(sf::Color(180, 0, 0, 255));
		}
		else
		{
			std::cout << "NOOOOOOO";
			tabLifeCircle[actualLife].setFillColor(sf::Color(0, 0, 0, 0));
		}
	}
	std::cout << actualLife << " / " << lifeChange << std::endl;
	return actualLife += lifeChange; // arthur t'es trop con ca augmente ta vie ici meme si tu en as 3, faut juste gerer la vie dans les if enculé
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

void SetPositionLifeCircle(sf::CircleShape tabLifeCircle[], float circleLifeRadius)
{
	float posX = 50;
	for(int i = 0; i < 3; i++)
	{
		tabLifeCircle[i].setPosition(posX, 100);
		posX += circleLifeRadius * 2 + 20;
	}
}