#include <SFML/Graphics.hpp>
#include "windows.h"
#include "Arthur.h"
#include "AssetsPath.h"
#include <iostream>

bool isButtonPressed(sf::Vector2f position, sf::Vector2f size, int mousePositionX, int mousePositionY)
{
	//std::cout << "Position : " << position.x << "/" << position.y << " - Scale : " << scale.x << "/" << scale.y << " - Mouse :" << mousePositionX << "/" << mousePositionY << std::endl;
	if (mousePositionX >= position.x && mousePositionX <= (position.x + size.x) && mousePositionY >= position.y && mousePositionY <= (position.y + size.y))
	{
		return true;
	}
	return false;
}

void SetButton(sf::RectangleShape& button, sf::Vector2f positionButton, sf::Vector2f sizeButton, sf::Color colorButton, sf::Color colorButtonThick, sf::Text& textButton, sf::String texte, sf::Color colorText, int sizeText)
{
	button.setSize(sizeButton);
	button.setPosition(positionButton);
	button.setFillColor(colorButton);
	button.setOutlineColor(colorButtonThick);
	button.setOutlineThickness(2);

	textButton.setFillColor(colorText);
	textButton.setCharacterSize(sizeText);
	textButton.setString(texte);
	textButton.setOrigin(textButton.getGlobalBounds().width / 2, textButton.getGlobalBounds().height / 2 + 5);
	textButton.setPosition(positionButton.x + (sizeButton.x / 2), positionButton.y + (sizeButton.y / 2));
}

void changeColor(int& actualColor, sf::Color& color1, sf::Color& color2)
{
	actualColor++;

	switch(actualColor)
	{
	case 1 :
		color1 = sf::Color::Black;
		color2 = sf::Color::White;
		break;
	case 2:
		color1 = sf::Color::Green;
		color2 = sf::Color::Red;
		break;
	case 3:
		color1 = sf::Color::Blue;
		color2 = sf::Color::Yellow;
		actualColor = 0;
		break;
	default:
		break;
	}
}

void setChangeColor(sf::RectangleShape& button, sf::Text& textButton, sf::Color color1, sf::Color color2)
{
	button.setFillColor(color1);
	button.setOutlineColor(color2);
	textButton.setFillColor(color2);
}

void setTitle(sf::Text& titleText, sf::Vector2f screenResolution)
{
	titleText.setFillColor(sf::Color::Black);
	titleText.setOutlineThickness(3);
	titleText.setOutlineColor(sf::Color::White);
	titleText.setCharacterSize(150);
	titleText.setString("Mega Black Hole");
	titleText.setOrigin(titleText.getGlobalBounds().width / 2, titleText.getGlobalBounds().height / 2 + 5);
	titleText.setPosition(screenResolution.x / 2, screenResolution.y / 5);
}