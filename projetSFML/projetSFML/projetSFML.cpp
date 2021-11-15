#include <SFML/Graphics.hpp>
#include "windows.h"
#include <iostream>
#include <list>
#include <vector>

#include "Colors.h"
#include "Bonus.h"

#include "Arthur.h"
#include "2D.h"
#include "Entities.h"
#include "BlackHole.h"
#include "AssetsPath.h"

int main()
{
	std::cout << std::boolalpha;

	std::list<Entity> entities;

	//bool isAnimating = false;

	// Window
	Vector2 screenResolution(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
	Vector2 middleScreen(screenResolution.x / 2, screenResolution.y / 2);
	sf::RenderWindow window(sf::VideoMode(screenResolution.x, screenResolution.y), "Mega Black Hole", sf::Style::Fullscreen);
	window.setVerticalSyncEnabled(true);

	bool isShowed = false;

	// Cercle du Jeu
	sf::CircleShape circleGame = CircleGameCrea(middleScreen.x, middleScreen.y);

	//Actuel Player
	Player playerOne = NewPlayer(PlayerCrea(circleGame, 1), 3, 1);
	Player playerTwo = NewPlayer(PlayerCrea(circleGame, 2), 3, 2);

	//ColorID idC = ColorID::BLACK;
	Colors playerColor = { sf::Color::Black, sf::Color::White };
	Colors playerColor2 = { sf::Color::Black, sf::Color::White };
	Colors colorEntities = { sf::Color::Black, sf::Color::White };
	playerOne.player.setOutlineThickness(3);
	playerTwo.player.setOutlineThickness(3);

	ColorID idC = ColorID::BLACK;

	//Point de vie Affichage
	SetPositionLifeCircle(playerOne, 20, screenResolution.x);
	SetPositionLifeCircle(playerTwo, 20, screenResolution.x);

	//Clock
	sf::Clock clock;
	sf::Clock scorePlayerOne;
	sf::Clock scorePlayerTwo;
	sf::Clock animTimer;
	sf::Clock timerBonus;
	sf::Clock timerColorChange;
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

	//Initialize balck holes and attacks
		// Create black hole
	BlackHole blackHole(middleScreen, 0.5f);


	//GESTION DU MENU
	sf::RectangleShape playButton;
	sf::Text playText;
	playText.setFont(arial);
	SetButton(playButton, sf::Vector2f(200, 200), sf::Vector2f(400, 200), sf::Color(0, 100, 150), sf::Color(255, 255, 255), playText, "LANCE MOI CA", sf::Color(150, 150, 0), 20);


	//PURE TESTING POUR AFFICHER LES COORD // A METTRE DANS LE MAIN SI BESOIN
	sf::Font test;
	test.loadFromFile(getAssetPath() + "PIXEAB__.TTF");
	sf::Text affichage;
	affichage.setFont(test);
	affichage.setPosition(100, 300);

	sf::Text yolo;
	yolo.setString("salutcava");
	yolo.setFont(test);
	yolo.setPosition(100, 300);


	// Game loop
	while (window.isOpen()) {
		if(getState() == GameState::MENU)
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
					window.close();
				}
				if (event.mouseButton.button == sf::Mouse::Left && isButtonPressed(playButton.getPosition(), playButton.getSize(), event.mouseButton.x, event.mouseButton.y))
				{
					setGameState(GameState::JEU);
				}
			}

			affichage.setString(std::to_string(yolo.getString().getSize()));

			window.clear();

			//Affichage Arthur
			window.draw(playButton);
			window.draw(playText);

			window.display();
		}
		else if(getState() == GameState::JEU)
		{
			//R�initialise la couleur du player
			playerOne.player.setFillColor(playerColor.primary);
			playerOne.player.setOutlineColor(playerColor.secondary);
			playerTwo.player.setFillColor(playerColor2.primary);
			playerTwo.player.setOutlineColor(playerColor2.secondary);

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
					playerColor = ChangeSide(playerColor, 1);
					//newBonus = SpawnBonus(bonus, isShowed, timerBonus);
				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M) {
					playerColor2 = ChangeSide(playerColor2, 2);
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

			if(playerOne.actualLife > 0) Deplacement(playerOne, elapsedTime);
			if(playerTwo.actualLife > 0) Deplacement(playerTwo, elapsedTime);

			//Deplacement(bonus, elapsedTime);
			if (timerColorChange.getElapsedTime().asSeconds() >= 10) {
				ChangeColorForEverything(playerColor, playerColor2, colorEntities, idC);
				timerColorChange.restart();
			}
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
			HandleEntities(&entities, &window, middleScreen, circleRadius, elapsedTime.asSeconds(),
				Vector2::FromSFVector2f(CoordPlayer(playerOne.player, circleGame)),
				Vector2::FromSFVector2f(CoordPlayer(playerTwo.player, circleGame)),
				20,
				&touchingPlayer1, &touchingPlayer2, colorEntities);

			// Check if there is collider touching player 1
			if (!touchingPlayer1.empty() && playerOne.actualLife > 0)
			{
				bool takeDamage = false;

				for (Entity* entite : touchingPlayer1)
				{
					sf::Color entityColor = entite->primaryColor ? colorEntities.primary : colorEntities.secondary;
					if (entityColor != playerColor.primary)
					{
						DestroyEntity(entite, &entities);
						takeDamage = true;
					}
				}
				if (takeDamage) setLife(playerOne, -1, scorePlayerOne);
			}
			// Check if there is collider touching player 2
			if (!touchingPlayer2.empty() && playerTwo.actualLife > 0)
			{
				bool takeDamage = false;

				for (Entity* entite : touchingPlayer2)
				{
					sf::Color entityColor = entite->primaryColor ? colorEntities.primary : colorEntities.secondary;
					if (entityColor != playerColor2.primary)
					{
						DestroyEntity(entite, &entities);
						takeDamage = true;
					}
				}
				if (takeDamage) setLife(playerTwo, -1, scorePlayerTwo);
			}

			//Affichage Arthur
			window.draw(circleGame);
			if(playerOne.actualLife > 0) window.draw(playerOne.player);
			if(playerTwo.actualLife > 0) window.draw(playerTwo.player);

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
}
