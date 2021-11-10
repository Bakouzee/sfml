#include <SFML/Graphics.hpp>
#include "windows.h"
#include <iostream>
#include <list>
#include <vector>

#include "Colors.h"
#include "Bonus.h"

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

	//bool isAnimating = false;

	// Window
	Vector2 screenResolution(1080, 720);
	Vector2 middleScreen(screenResolution.x / 2, screenResolution.y / 2);
	sf::RenderWindow window(sf::VideoMode(screenResolution.x, screenResolution.y), "ChronoSpacer");
	window.setVerticalSyncEnabled(true);

	bool isShowed = false;

	// Cercle du Jeu
	sf::CircleShape circleGame = CircleGameCrea(middleScreen.x, middleScreen.y);

	//Actuel Player
	Player playerOne = NewPlayer(PlayerCrea(circleGame), 3, 1);
	Player playerTwo = NewPlayer(PlayerCrea(circleGame), 3, 2);

	//ColorID idC = ColorID::BLACK;
	Colors playerColor = { sf::Color::Black, sf::Color::White };
	playerOne.player.setOutlineThickness(5);

	//Point de vie Affichage
	SetPositionLifeCircle(playerOne, 20, screenResolution.x);
	SetPositionLifeCircle(playerTwo, 20, screenResolution.x);

	//Clock
	sf::Clock clock;
	sf::Clock scorePlayerOne;
	sf::Clock scorePlayerTwo;
	sf::Clock animTimer;
	sf::Clock timerBonus;
	//sf::Clock timer;

	//Bonus
	sf::CircleShape bonus = BonusCrea(circleGame);
	sf::CircleShape newBonus;

	//Score
	sf::Font arial;
	arial.loadFromFile(getAssetPath() + "\\arial.ttf");
	sf::Text scorePlayerOneText = SetText(1, screenResolution.x);
	scorePlayerOneText.setFont(arial);
	sf::Text scorePlayerTwoText = SetText(2, screenResolution.x);
	scorePlayerTwoText.setFont(arial);
	// Initialise everything below

	//Initialize balck holes and attacks
		// Creat possible attacks
	std::list<AttackPattern> attacks;
	attacks.push_back(AttackPattern(4, 1, 0.5f, 5, 0.5 * circleRadius));
		// Create black hole
	BlackHole blackHole(middleScreen, 0.5f, attacks);

	// Game loop
	while (window.isOpen()) {
		//R�initialise la couleur du player
		playerOne.player.setFillColor(playerColor.primary);
		playerOne.player.setOutlineColor(playerColor.secondary);

		// Clock
		sf::Time elapsedTime = clock.restart(); // elapsedTime.asSeconds() pour l'utiliser
		if(playerOne.actualLife > 0)
		{
			SetScore(scorePlayerOne.getElapsedTime().asSeconds(), scorePlayerOneText, 1);
		}
		if (playerTwo.actualLife > 0)
		{
			SetScore(scorePlayerTwo.getElapsedTime().asSeconds(), scorePlayerTwoText, 2);
		}

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


		//float timeChangingColors = timer.getElapsedTime().asSeconds();
		//if (timeChangingColors >= 3) {
		//	ChangeColorForEverything(playerColor, //color des entit�s, idC);
		//}

		//Score Animation
		//float anim = animTimer.getElapsedTime().asSeconds();
		//score.setOrigin(score.getLocalBounds().width / 2, score.getLocalBounds().height / 2);

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
				newBonus = SpawnBonus(bonus, isShowed, timerBonus);
			}
			else if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			{
				float angle = rand();
				float speed = rand() % 25 + 50;
				Vector2 dir = Vector2(cos(angle), sin(angle));
				bool primaryColor = rand() % 2 == 0;
				entities.push_back(Entity(middleScreen, dir, speed, primaryColor, MinMax(5, 20)));
			}
			/*else if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::L))
			{
				setLife(playerOne, 1);
			}*/
		}
		Deplacement(playerOne, elapsedTime);
		Deplacement(playerTwo, elapsedTime);
		//Deplacement(bonus, elapsedTime);

		window.clear();
		// Whatever I want to draw goes here
		if (timerBonus.getElapsedTime().asSeconds() >= 3) {
			isShowed = false;
		}
		if (isShowed) {
			window.draw(newBonus);
		}
			

		// Entities gestion
		std::vector<Entity*> touchingPlayer1;
		std::vector<Entity*> touchingPlayer2;
		HandleEntities(&entities, &window, middleScreen, 250, elapsedTime.asSeconds(),
			Vector2::FromSFVector2f(CoordPlayer(playerOne.player, circleGame)), 
			Vector2::FromSFVector2f(CoordPlayer(playerTwo.player, circleGame)), 
			20,
			&touchingPlayer1, &touchingPlayer2, playerColor);

		// Check if there is collider touching player 1
		if(!touchingPlayer1.empty())
		{
			for(Entity* entite : touchingPlayer1)
			{
				DestroyEntity(entite, &entities);
			}
			setLife(playerOne, -1);
		}
		if(!touchingPlayer2.empty())
		{
			for(Entity* entite : touchingPlayer2)
			{
				DestroyEntity(entite, &entities);
			}
			setLife(playerTwo, -1);
		}

		//Affichage Arthur
		window.draw(circleGame);
		window.draw(playerOne.player);
		window.draw(playerTwo.player);

		for (int i = 0; i < 3; i++)
		{
			window.draw(playerOne.tabLifeCircle[i]);
			window.draw(playerTwo.tabLifeCircle[i]);
		}

		//Affichage score
		window.draw(scorePlayerOneText);
		window.draw(scorePlayerTwoText);

		window.display();
	}
}
