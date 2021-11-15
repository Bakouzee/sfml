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
	textButton.setOrigin(textButton.getLocalBounds().width / 2, textButton.getLocalBounds().height / 2);
	textButton.setPosition(positionButton.x + (sizeButton.x / 2), positionButton.y + (sizeButton.y / 2));
}