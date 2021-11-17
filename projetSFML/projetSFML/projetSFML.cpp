#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "windows.h"
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>

#include "AudioManager.h"
#include "Colors.h"

#include "Arthur.h"
#include "2D.h"
#include "Entities.h"
#include "BlackHole.h"
#include "AssetsPath.h"

#include "Bonus.h"
#include "Gamefeel.h"

#include "attacks_pattern_json_reader.h"

int main()
{
	std::cout << std::boolalpha;

	SetUpAudios();

	std::list<Entity> entities;

	//bool isAnimating = false;

	// Window
	Vector2 screenResolution(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
	Vector2 middleScreen(screenResolution.x / 2, screenResolution.y / 2);
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(screenResolution.x, screenResolution.y), "Mega Black Hole", sf::Style::Default, settings); //, sf::Style::Fullscreen
	window.setVerticalSyncEnabled(true);

	bool isShowed = false;
	float comboJ1 = 1.f;
	float comboJ2 = 1.f;
	float scoreJ1 = 0.f;
	float scoreJ2 = 0.f;


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

	//Gamefeel
	int x = middleScreen.x - circleRadius;
	int y = middleScreen.y;
	bool arcHG = false;
	bool arcHD = false;
	bool arcBD = false;
	bool arcBG = false;

	//Clock
	sf::Clock clock;
	sf::Clock scorePlayerOne;
	sf::Clock scorePlayerTwo;
	sf::Clock animTimer;
	sf::Clock timerBonus;
	sf::Clock timerColorChange;
	sf::Clock timerComboJ1;
	sf::Clock timerComboJ2;

	sf::Clock timerColorChangeMenu;
	//sf::Clock timer;

	//Bonus
	sf::CircleShape bonus;

	//Score
	sf::Font arial;
	arial.loadFromFile(getAssetPath() + "\\arial.ttf");
	sf::Text scorePlayerOneText = SetText(1, screenResolution.x);
	scorePlayerOneText.setFont(arial);
	sf::Text scorePlayerTwoText = SetText(2, screenResolution.x);
	scorePlayerTwoText.setFont(arial);

	//Initialize balck holes and attacks
		// Create attack
	std::vector<AttackPattern> results = GetAllAttacks();
		// Create black hole
	BlackHole blackHole(middleScreen, 0.5f, &results);


	//GESTION DU MENU
	int actualColor = 1;

	sf::Font titlefont;
	titlefont.loadFromFile(getAssetPath() + "\\TitreFont.otf");
	sf::Text titleText;
	titleText.setFont(titlefont);
	titleText.setFillColor(sf::Color::Black);
	titleText.setOutlineThickness(3);
	titleText.setOutlineColor(sf::Color::White);
	titleText.setCharacterSize(150);
	titleText.setString("Mega Black Hole");
	titleText.setOrigin(titleText.getGlobalBounds().width / 2, titleText.getGlobalBounds().height / 2 + 5);
	titleText.setPosition(screenResolution.x / 2, screenResolution.y / 5);

	float tailleButtonX = screenResolution.x / 8;
	float tailleButtonY = screenResolution.y / 12;

	sf::RectangleShape J1Button;
	sf::Text J1Text;
	J1Text.setFont(titlefont);
	SetButton(J1Button, sf::Vector2f(screenResolution.x / 2 - (tailleButtonX + screenResolution.x / 50), screenResolution.y / 2), sf::Vector2f(tailleButtonX, tailleButtonY), sf::Color::Black, sf::Color::White, J1Text, "1 Player", sf::Color::White, 40);

	sf::RectangleShape J2Button;
	sf::Text J2Text;
	J2Text.setFont(titlefont);
	SetButton(J2Button, sf::Vector2f(screenResolution.x / 2 + screenResolution.x / 50, screenResolution.y / 2), sf::Vector2f(tailleButtonX, tailleButtonY), sf::Color::Black, sf::Color::White, J2Text, "2 Players", sf::Color::White, 40);
	bool isPlayerTwo = false;

	sf::RectangleShape quitButton;
	sf::Text quitText;
	quitText.setFont(titlefont);
	SetButton(quitButton, sf::Vector2f(screenResolution.x / 2 - screenResolution.x / 16, screenResolution.y / 2 + tailleButtonY + screenResolution.y / 30), sf::Vector2f(tailleButtonX, tailleButtonY), sf::Color::Black, sf::Color::White, quitText, "Quit", sf::Color::White, 40);

	// Game loop
	while (window.isOpen()) {
		if(getState() == GameState::MENU)
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) || isButtonPressed(quitButton.getPosition(), quitButton.getSize(), event.mouseButton.x, event.mouseButton.y)) {
					window.close();
				}
				if (event.mouseButton.button == sf::Mouse::Left && isButtonPressed(J1Button.getPosition(), J1Button.getSize(), event.mouseButton.x, event.mouseButton.y))
				{
					setGameState(GameState::JEU);
				}
				if (event.mouseButton.button == sf::Mouse::Left && isButtonPressed(J2Button.getPosition(), J2Button.getSize(), event.mouseButton.x, event.mouseButton.y))
				{
					setGameState(GameState::JEU);
					isPlayerTwo = true;
				}
			}

			if (timerColorChangeMenu.getElapsedTime().asSeconds() > 5)
			{
				sf::Color color1;
				sf::Color color2;
				changeColor(actualColor, color1, color2);

				//titleText.setFillColor(color1);
				//titleText.setOutlineColor(color2);

				setChangeColor(J1Button, J1Text, color1, color2);
				setChangeColor(J2Button, J2Text, color1, color2);
				setChangeColor(quitButton, quitText, color1, color2);
				timerColorChangeMenu.restart();
			}

			window.clear();

			//Affichage Arthur
			window.draw(titleText);
			window.draw(J1Button);
			window.draw(J2Button);
			window.draw(quitButton);
			window.draw(J1Text);
			window.draw(J2Text);
			window.draw(quitText);

			window.display();
		}
		else if(getState() == GameState::JEU)
		{
			//R�initialise la couleur du player
			playerOne.player.setFillColor(playerColor.primary);
			playerOne.player.setOutlineColor(playerColor.secondary);
			if(isPlayerTwo)
			{
				playerTwo.player.setFillColor(playerColor2.primary);
				playerTwo.player.setOutlineColor(playerColor2.secondary);
			}

			// Clock
			sf::Time elapsedTime = clock.restart(); // elapsedTime.asSeconds() pour l'utiliser
			if (playerOne.actualLife > 0)
			{
				scoreJ1 = SetScore(scorePlayerOne.getElapsedTime().asSeconds(), scorePlayerOneText, 1, comboJ1, scoreJ1);
			}
			if (playerTwo.actualLife > 0 && isPlayerTwo)
			{
				scoreJ2 = SetScore(scorePlayerTwo.getElapsedTime().asSeconds(), scorePlayerTwoText, 2, comboJ2, scoreJ2);
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
					//bonus pour 2j
					bonus = BonusCrea2J(playerOne.player, playerTwo.player, circleGame);
					float distancePlayers = (playerOne.player.getRotation() + playerTwo.player.getRotation()) / 2;
					if (distancePlayers <= 180.f) {
						bonus.setRotation(distancePlayers - 180.f);
					}
					else {
						bonus.setRotation(distancePlayers + 180.f);
					}
					ChooseBonus(bonus, isShowed, timerBonus);

				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M) {
					playerColor2 = ChangeSide(playerColor2, 2);
					//bonus pour 1J
					bonus = BonusCrea1J(playerOne.player, circleGame);
					ChooseBonus(bonus, isShowed, timerBonus);
				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
					PlayHurtSound();
				}
				else if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::E))
				{
					float angle = rand();
					float speed = rand() % 25 + 50;
					Vector2 dir = Vector2(cos(angle), sin(angle));
					bool primaryColor = rand() % 2 == 0;
					entities.push_back(Entity(middleScreen, dir, speed, primaryColor, MinMax(5, 20)));
				}
			}

			if (timerColorChange.getElapsedTime().asSeconds() >= 10) {
			ChangeColorForEverything(playerColor, playerColor2, colorEntities, idC);
			timerColorChange.restart();
		}
			window.clear();

			if (bonus.getFillColor() == sf::Color::Red) {

				float rotationBonusMin = bonus.getRotation() - 5;
				float rotationBonusMax = bonus.getRotation() + 5;

				std::cout << "Bonus rotation : " << rotationBonusMin << ", " << rotationBonusMax << "[" << bonus.getRotation() << "]" << std::endl;
				std::cout << "Player rotation : " << playerOne.player.getRotation() + 180 << std::endl;
				if (playerOne.player.getRotation() <= 180) {
					std::cout << " - 180" << std::endl;
					if (playerOne.player.getRotation() + 180 <= rotationBonusMax && playerOne.player.getRotation() + 180 >= rotationBonusMin) {
						std::cout << "hit" << std::endl;
						setLife(playerOne, 1, timerBonus);
						isShowed = false;
					}
				}
				else {
					if (playerOne.player.getRotation() - 180 <= rotationBonusMax && playerOne.player.getRotation() - 180 >= rotationBonusMin) {
						std::cout << "hit" << std::endl;
						setLife(playerOne, 1, timerBonus);
						isShowed = false;
					}
				}
				if (playerTwo.player.getRotation() <= 180) {
					std::cout << " - 180" << std::endl;
					if (playerTwo.player.getRotation() + 180 <= rotationBonusMax && playerTwo.player.getRotation() + 180 >= rotationBonusMin) {
						std::cout << "hit" << std::endl;
						setLife(playerTwo, 1, timerBonus);
						isShowed = false;
					}
				} else {
					if (playerTwo.player.getRotation() - 180 <= rotationBonusMax && playerTwo.player.getRotation() - 180 >= rotationBonusMin) {
						std::cout << "hit" << std::endl;
						setLife(playerTwo, 1, timerBonus);
						isShowed = false;
					}
				}
			}

			// Whatever I want to draw goes here
			if (timerBonus.getElapsedTime().asSeconds() >= 3) {
				isShowed = false;
			}
			if (isShowed) {
				window.draw(bonus);
			}				

			if(playerOne.actualLife > 0) Deplacement(playerOne, elapsedTime);
			if(playerTwo.actualLife > 0 && isPlayerTwo) Deplacement(playerTwo, elapsedTime);

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
				window.draw(bonus);
			}

			// Entities gestion
			std::vector<Entity*> touchingPlayer1;
			std::vector<Entity*> touchingPlayer2;
			HandleEntities(&entities, &window, middleScreen, circleRadius, elapsedTime.asSeconds(),
			Vector2::FromSFVector2f(CoordPlayer(playerOne.player, circleGame)),
			Vector2::FromSFVector2f(CoordPlayer(playerTwo.player, circleGame)),	20,	&touchingPlayer1, &touchingPlayer2, colorEntities);

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
						comboJ1 = 0.f;
					} else {
						comboJ1 += 0.3f;
						timerComboJ1.restart();
						if (timerComboJ1.getElapsedTime().asSeconds() >= 1.5f) {
							comboJ1 = 0.f;
						}
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
						comboJ2 = 0.f;
					} else {
						comboJ2 += 0.3f;
						timerComboJ2.restart();
						if (timerComboJ2.getElapsedTime().asSeconds() >= 1.5f) {
							comboJ2 = 0.f;
						}
					}
				}
				if (takeDamage) setLife(playerTwo, -1, scorePlayerTwo);				
			}

		//Affichage Arthur
		window.draw(circleGame);
		if (playerOne.actualLife > 0)
			window.draw(playerOne.player);
		if (playerTwo.actualLife > 0)
			window.draw(playerTwo.player);
		for (int i = 0; i < 3; i++)
		{
			window.draw(playerOne.tabLifeCircle[i]);
			if (isPlayerTwo)
				window.draw(playerTwo.tabLifeCircle[i]);
		}

		//Gamefeel
		/*for (int i = 0; i < 360; i++) {
			sf::Vertex vertexCenter;
			vertexCenter.position = sf::Vector2f(middleScreen.x, middleScreen.y);
			vertexCenter.color = sf::Color::Black;

			sf::Vertex vertexCircle;
			vertexCircle.position = sf::Vector2f(x, y);
			vertexCircle.color = sf::Color::Red;

			sf::VertexArray line(sf::LineStrip, 2);
			line[0].position = vertexCenter.position;
			line[0].color = vertexCenter.color;
			line[1].position = vertexCircle.position;
			line[1].color = vertexCircle.color;

			window.draw(line);

			if (x == middleScreen.x - circleRadius && y == middleScreen.y) {
				arcHG = true;
				arcHD = false;
				arcBD = false;
				arcBG = false;
			}
			if (arcHG) {
				x += 1;
				y -= 1;
			}
			if (x == middleScreen.x && y == middleScreen.y - circleRadius) {
				arcHG = false;
				arcHD = true;
				arcBD = false;
				arcBG = false;
			}
			if (arcHD) {
				x += 1;
				y += 1;
			}
			if (x == middleScreen.x + circleRadius && y == middleScreen.y) {
				arcHG = false;
				arcHD = false;
				arcBD = true;
				arcBG = false;
			}
			if (arcBD) {
				x -= 1;
				y += 1;
			}
			if (x == middleScreen.x && y == middleScreen.y + circleRadius) {
				arcHG = false;
				arcHD = false;
				arcBD = false;
				arcBG = true;
			}
			if (arcBG) {
				x -= 1;
				y -= 1;
			}
		}*/

		//Affichage score
		window.draw(scorePlayerOneText);
		window.draw(scorePlayerTwoText);
		//Affichage score
		window.draw(scorePlayerOneText);
		if (isPlayerTwo)
			window.draw(scorePlayerTwoText);

		window.display();

		}
	}
}
