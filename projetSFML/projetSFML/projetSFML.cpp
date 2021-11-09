#include <SFML/Graphics.hpp>
#include "windows.h"
#include <iostream>
#include <list>
#include <vector>

#include "Arthur.h"
#include "Entities.h"

std::string getAppPath() {
	char cExeFilePath[256];
	GetModuleFileNameA(NULL, cExeFilePath, 256);
	std::string exeFilePath = cExeFilePath;
	int exeNamePos = exeFilePath.find_last_of("\\/");
	std::string appPath = exeFilePath.substr(0, exeNamePos + 1);
	return appPath;
}

std::string getAssetPath() {
	return getAppPath() + "Assets\\";
}

int main()
{
	std::cout << std::boolalpha;

	std::list<Entity> entities;

	sf::Clock clock;
	Vector2 screenResolution(800, 600);
	Vector2 middleScreen(screenResolution.x / 2, screenResolution.y / 2);
	sf::RenderWindow window(sf::VideoMode(screenResolution.x, screenResolution.y), "ChronoSpacer");
	// Initialise everything below
	// Game loop
	while (window.isOpen()) {
		clock.restart();
		sf::Event event;
		while (window.pollEvent(event)) {
			// Process any input event here
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			else if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			{
				float angle = rand();
				float speed = rand() % 25 + 50;
				Vector2 dir = Vector2(cos(angle), sin(angle)) * speed;
				bool primaryColor = rand() % 2 == 0;
				entities.push_back(Entity(Vector2(400,300), dir, primaryColor, MinMax(5, 20)));
			}
		}

		// Checks collision
		std::vector<Entity*> touchingEntities;
		if(CheckCollisions(middleScreen, 250, &entities, &touchingEntities))
		{
			// Do whattever you want to the entities touching stored in touchingEntities
		}

		window.clear();
		// Whatever I want to draw goes here
		DrawEntities(&entities, &window);

		window.display();

		// Move entities
		MoveEntities(&entities, clock.getElapsedTime().asSeconds());

		// Destroy entities if too far
		DestroyFarEntities(middleScreen, 250, &entities);
	}
}