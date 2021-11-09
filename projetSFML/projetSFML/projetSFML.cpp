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

	Vector2 screenResolution(800, 600);
	Vector2 middleScreen(screenResolution.x / 2, screenResolution.y / 2);
	sf::RenderWindow window(sf::VideoMode(screenResolution.x, screenResolution.y), "ChronoSpacer");
	window.setVerticalSyncEnabled(true);

	// Cercle du Jeu
	sf::CircleShape circleGame = CircleGameCrea(middleScreen.x, middleScreen.y);

	//Actuel Player
	sf::CircleShape player = PlayerCrea(20, circleGame);

	//Clock
	sf::Clock clock;

	// Initialise everything below
	// Game loop
	while (window.isOpen()) {

		// Clock
		sf::Time elapsedTime = clock.restart(); // elapsedTime.asSeconds() pour l'utiliser

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

			Deplacement(player, elapsedTime);
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

		//Affichage Arthur
		window.draw(circleGame);
		window.draw(player);

		window.display();

		// Move entities
		MoveEntities(&entities, elapsedTime.asSeconds());

		// Destroy entities if too far
		DestroyFarEntities(middleScreen, 250, &entities);
	}
}