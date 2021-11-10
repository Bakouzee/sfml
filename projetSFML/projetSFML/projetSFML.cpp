#include <SFML/Graphics.hpp>
#include "windows.h"
#include <iostream>
#include <list>
#include <vector>

#include "Colors.h"
#include "Bonus.h"

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

	//bool isAnimating = false;

	// Window
	Vector2 screenResolution(1080, 720);
	Vector2 middleScreen(screenResolution.x / 2, screenResolution.y / 2);
	sf::RenderWindow window(sf::VideoMode(screenResolution.x, screenResolution.y), "ChronoSpacer");
	window.setVerticalSyncEnabled(true);

	// Cercle du Jeu
	sf::CircleShape circleGame = CircleGameCrea(middleScreen.x, middleScreen.y);

	//Actuel Player
	//ColorID idC = ColorID::BLACK;
	Colors playerColor = { sf::Color::Black, sf::Color::White };
	sf::CircleShape player = PlayerCrea(20, circleGame);
	player.setOutlineThickness(5);

	//Lifes
	std::vector<sf::CircleShape> lives(3, sf::CircleShape(30, 3));
	float xLife = 20;
	for (auto it = lives.begin(); it != lives.end(); it++) {
		(*it).setFillColor(sf::Color::Red);
		(*it).setPosition(xLife, 650);
		xLife += 70;
	}
	

	//Clock
	sf::Clock clock;
	sf::Clock scoreGame;
	sf::Clock animTimer;
	//sf::Clock timer;

	//Score
	sf::Font arial;
	arial.loadFromFile(getAssetPath() + "\\arial.ttf");
	sf::Text score;
	score.setFont(arial);
	score.setCharacterSize(20);
	score.setPosition(middleScreen.x, 15);
	score.setOutlineColor(sf::Color::White);
	score.setOutlineThickness(1);
	score.setFillColor(sf::Color::Black);
	// Initialise everything below


	// Game loop
	while (window.isOpen()) {
		//R�initialise la couleur du player
		player.setFillColor(playerColor.primary);
		player.setOutlineColor(playerColor.secondary);

		// Clock
		sf::Time elapsedTime = clock.restart(); // elapsedTime.asSeconds() pour l'utiliser
		float deltaTime = scoreGame.getElapsedTime().asSeconds();
		deltaTime *= deltaTime * 100;

		//float timeChangingColors = timer.getElapsedTime().asSeconds();
		//if (timeChangingColors >= 3) {
		//	ChangeColorForEverything(playerColor, //color des entit�s, idC);
		//}

		//Score
		score.setString("Score : " + std::to_string((int)deltaTime));
		float anim = animTimer.getElapsedTime().asSeconds();
		score.setOrigin(score.getLocalBounds().width / 2, score.getLocalBounds().height / 2);

		/*if ((int)deltaTime % 1000 == 0 && (int)deltaTime > 0) {
			isAnimating = true;
			std::cout << isAnimating << std::endl;
		}

		if (isAnimating) {
			animTimer.restart();
			if (anim <= 1.3f) {
				score.setCharacterSize(score.getCharacterSize() + 1);
			} else {
				score.setCharacterSize(30);
				isAnimating = false;
			}
		}*/
		

		sf::Event event;
		while (window.pollEvent(event)) {
			// Process any input event here
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A) {
				playerColor = ChangeSide(playerColor);					
			}
			else if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			{
				float angle = rand();
				float speed = rand() % 25 + 50;
				Vector2 dir = Vector2(cos(angle), sin(angle)) * speed;
				bool primaryColor = rand() % 2 == 0;
				entities.push_back(Entity(middleScreen, dir, primaryColor, MinMax(5, 20)));
			}

		}
		Deplacement(player, elapsedTime);

		window.clear();
		// Whatever I want to draw goes here

		// Entities gestion
		std::vector<Entity*> touchingEntities;
		HandleEntities(&entities, &window, middleScreen, 250, Vector2::FromSFVector2f(CoordPlayer(player, circleGame)),
			20, elapsedTime.asSeconds(), &touchingEntities);
			// Check if there is collider touching player
		if(!touchingEntities.empty())
		{
			// Here le code en cas de collision entre une entité et un joueur
			lives.pop_back();
			
		}

		//Affichage Arthur
		window.draw(circleGame);
		window.draw(player);
		//window.draw(affichage);
		
		//Affichage vies
		for (auto it = lives.begin(); it != lives.end(); it++) {
			window.draw(*it);
		}

		//Affichage score
		window.draw(score);

		window.display();
	}
}
