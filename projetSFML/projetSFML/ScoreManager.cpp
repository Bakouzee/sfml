#include <SFML/Graphics.hpp>
#include "windows.h"
#include "Arthur.h"
#include <iostream>

sf::Text SetText(int numberPlayer, float screenResolutionX)
{
	sf::Text actualText;
	actualText.setCharacterSize(20);
	if(numberPlayer == 1)
	{
		actualText.setPosition(40, 30);
	}
	else
	{
		actualText.setPosition(screenResolutionX - 180, 30);
	}
	return actualText;
}

float SetScore(float actualTime, sf::Text& actualText, int numberPlayer, float combo, float score)
{
	score += actualTime * actualTime * 10 * combo;
	actualText.setString("Score J" + std::to_string(numberPlayer) + " : " + std::to_string((int)score));
	return score;
}