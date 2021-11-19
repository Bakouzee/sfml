#include <SFML/Graphics.hpp>
#include "windows.h"
#include "Arthur.h"
#include <iostream>

void SetText(sf::Text& actualText, int numberPlayer, sf::Vector2f screenResolution, bool isPlayerTwoActive)
{
	actualText.setCharacterSize(20);
	actualText.setOrigin(actualText.getGlobalBounds().width / 2, actualText.getGlobalBounds().height / 2 + 5);
	if(getState() == GameState::MENU || getState() == GameState::JEU)
	{
		if(numberPlayer == 1)
		{
			actualText.setPosition(screenResolution.x / 64 * 2, screenResolution.y / 30);
		}
		else
		{
			actualText.setPosition(screenResolution.x / 64 * 57, screenResolution.y / 30);
		}
	}
	else if(getState() == GameState::FIN)
	{
		actualText.setCharacterSize(40);
		if(isPlayerTwoActive)
		{
			if (numberPlayer == 0)
			{
				actualText.setPosition(screenResolution.x / 2 - 30, screenResolution.y / 7);
			}
			else if(numberPlayer == 1)
			{
				actualText.setPosition(screenResolution.x / 9 * 2, screenResolution.y / 3);
			}
			else
			{
				actualText.setPosition(screenResolution.x / 8 * 6, screenResolution.y / 3);
			}
		}
		else if(numberPlayer == 1)
		{
			actualText.setPosition(screenResolution.x / 2 - 30, screenResolution.y / 7);
		}
		else if (numberPlayer == 3)
		{
			actualText.setPosition(screenResolution.x / 2 - 30, screenResolution.y / 7 * 3);
		}
	}
}


float SetScore(float actualTime, sf::Text& actualText, int numberPlayer, float combo, float score)
{
	score += actualTime * actualTime * 10 * combo;
	actualText.setString("Score J" + std::to_string(numberPlayer) + " : " + std::to_string((int)score));
	return score;
}
