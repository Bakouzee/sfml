#include <SFML/Graphics.hpp>
#include "windows.h"
#include <iostream>
#include <list>
#include <vector>

#include "Colors.h"

#include "Arthur.h"
#include "BlackHole.h"

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
	sf::CircleShape player = PlayerCrea(circleGame);
	player.setOutlineThickness(5);


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

	//Initialize balck holes and attacks
		// Creat possible attacks
	std::list<AttackPattern> attacks;
	attacks.push_back(AttackPattern(4, 1, 0.5f, 5, 0.5 * circleRadius));
		// Create black hole
	BlackHole blackHole(middleScreen, 0.5f, attacks);


	// Game loop
	while (window.isOpen()) {
		// Clock
		sf::Time elapsedTime = clock.restart(); // elapsedTime.asSeconds() pour l'utiliser
		float deltaTime = scoreGame.getElapsedTime().asSeconds();
		deltaTime *= deltaTime;

		// Black hole gestion
		if(blackHole.attackTimer <= 0)
		{
			blackHole.LaunchNewAttack(&entities);
		}
		else
		{
			blackHole.attackTimer = blackHole.attackTimer - elapsedTime.asSeconds();

			blackHole.currentAttackPtr->waveTimer = blackHole.currentAttackPtr->waveTimer - elapsedTime.asSeconds();
			blackHole.currentAttackPtr->SpawnWaveIfFinished(*(blackHole.position), &entities);
		}

		//std::cout << entities.size() << std::endl;

		//R�initialise la couleur du player
		player.setFillColor(playerColor.primary);
		player.setOutlineColor(playerColor.secondary);


		//float timeChangingColors = timer.getElapsedTime().asSeconds();
		//if (timeChangingColors >= 3) {
		//	ChangeColorForEverything(playerColor, //color des entit�s, idC);
		//}

		//Score
		score.setString("Score : " + std::to_string((int)deltaTime));
		float anim = animTimer.getElapsedTime().asSeconds();
		//score.setOrigin(score.getString().getSize() / 2, score.getOrigin().y);
		score.setOrigin(score.getLocalBounds().width / 2, score.getLocalBounds().height / 2);

		if (anim <= 1.5) {
			score.setCharacterSize(score.getCharacterSize() + 1);
		}
		else {
			score.setCharacterSize(30);
			animTimer.restart();
		}

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
				Vector2 dir = Vector2(cos(angle), sin(angle));
				bool primaryColor = rand() % 2 == 0;
				entities.push_back(Entity(middleScreen, dir, speed, primaryColor, MinMax(5, 20)));
			}

		}
		Deplacement(player, elapsedTime);

		window.clear();
		// Whatever I want to draw goes here

		// Entities gestion
		std::vector<Entity*> touchingPlayer1;
		std::vector<Entity*> touchingPlayer2;
		HandleEntities(&entities, &window, middleScreen, 250, elapsedTime.asSeconds(),
			Vector2::FromSFVector2f(CoordPlayer(player, circleGame)), 
			Vector2::FromSFVector2f(CoordPlayer(player, circleGame)), 
			20,
			&touchingPlayer1, &touchingPlayer2, playerColor);

		// Check if there is collider touching player 1
		if(!touchingPlayer1.empty())
		{
			for(Entity* entite : touchingPlayer1)
			{
				DestroyEntity(entite, &entities);
			}
		}
		if(!touchingPlayer2.empty())
		{
			for(Entity* entite : touchingPlayer2)
			{
				DestroyEntity(entite, &entities);
			}
		}

		//Affichage Arthur
		window.draw(circleGame);
		window.draw(player);

		//Affichage score
		window.draw(score);

		window.display();
	}
}
