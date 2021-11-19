#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "windows.h"
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>

#include "2D.h"

#include "AudioManager.h"
#include "Colors.h"

#include "Entities.h"
#include "Arthur.h"
#include "BlackHole.h"
#include "AssetsPath.h"

#include "file_reader.h"
#include "Bonus.h"
#include "Gamefeel.h"

#include "file_reader.h"

int main()
{
	// Better random and bool display
	std::cout << std::boolalpha;
	srand(time(NULL));

	// Audio and music
	SetUpAudios();
	PlayGameMusic();


	//bool isAnimating = false;

	// Window
	#pragma region Window definition
	Vector2 screenResolution(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
	Vector2 middleScreen(screenResolution.x / 2, screenResolution.y / 2);
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(screenResolution.x, screenResolution.y), "Mega Black Hole", sf::Style::Default, settings); //, sf::Style::Fullscreen
	window.setVerticalSyncEnabled(true);
	#pragma endregion

	bool isShowed = false;
	float comboJ1 = 1.f;
	float comboJ2 = 1.f;
	float scoreJ1 = 0.f;
	float scoreJ2 = 0.f;

	// Cercle du Jeu
	sf::CircleShape circleGame = CircleGameCrea(middleScreen.x, middleScreen.y);

	//Player
	int playerInGame = 0;
	bool isPlayerTwo = false;
	Player playerOne = NewPlayer(PlayerCrea(circleGame, 1), 3, 1);
	Player playerTwo = NewPlayer(PlayerCrea(circleGame, 2), 3, 2);

	// Pairs of color defintion --> apllied to projectiles and players
	#pragma region Pairs of color definitions
	Colors playerColor = { sf::Color::Black, sf::Color::White };
	Colors playerColor2 = { sf::Color::Black, sf::Color::White };
	Colors colorEntities = { sf::Color::Black, sf::Color::White };
	playerOne.player.setOutlineThickness(3);
	playerTwo.player.setOutlineThickness(3);

	ColorID idC = ColorID::BLACK;
	#pragma endregion

	// Set players life position (UI)
	SetPositionLifeCircle(playerOne, 20, screenResolution.x);
	SetPositionLifeCircle(playerTwo, 20, screenResolution.x);

	//Gamefeel
	int x = middleScreen.x - circleRadius;
	int y = middleScreen.y;
	bool arcHG = false;
	bool arcHD = false;
	bool arcBD = false;
	bool arcBG = false;

	//Clocks
	#pragma region Clocks definition
	sf::Clock clock;
	sf::Clock scorePlayerOne;
	sf::Clock scorePlayerTwo;
	sf::Clock animTimer;
	sf::Clock timerBonus;
	sf::Clock timerSpawnBonus;
	sf::Clock timerColorChange;
	sf::Clock timerComboJ1;
	sf::Clock timerComboJ2;

	sf::Clock timerColorChangeMenu;
	//sf::Clock timer;
	#pragma endregion

	//Bonus
	sf::CircleShape bonus;

	//Score
	#pragma region Score fonts and texts
	sf::Font arial;
	arial.loadFromFile(getAssetPath() + "\\arial.ttf");
	sf::Text scorePlayerOneText;
	SetText(scorePlayerOneText, 1, screenResolution.ToSFVector2f());
	scorePlayerOneText.setFont(arial);
	sf::Text scorePlayerTwoText;
	SetText(scorePlayerTwoText,2, screenResolution.ToSFVector2f());
	scorePlayerTwoText.setFont(arial);
	#pragma endregion

	//Initialize balck holes (struct instance managing projectiles creation)
	#pragma region Initialize black hole
		// Create attack
	std::vector<AttackPattern> results = GetAllAttacks();
		// Create black hole
	BlackHole blackHole(middleScreen, 0.5f, &results);
	#pragma endregion
	std::list<Entity> entities;

	// Main menu vars
	#pragma region Main menu buttons
	int actualColor = 1;

	sf::Font titlefont;
	titlefont.loadFromFile(getAssetPath() + "\\TitreFont.otf");
	sf::Text titleText;
	titleText.setFont(titlefont);
	setTitle(titleText, screenResolution.ToSFVector2f());

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

	sf::RectangleShape quitButton;
	sf::Text quitText;
	quitText.setFont(titlefont);
	SetButton(quitButton, sf::Vector2f(screenResolution.x / 2 - screenResolution.x / 16, screenResolution.y / 2 + tailleButtonY + screenResolution.y / 30), sf::Vector2f(tailleButtonX, tailleButtonY), sf::Color::Black, sf::Color::White, quitText, "Quit", sf::Color::White, 40);
	#pragma endregion

	// End Menu vars
	#pragma region End menu
	bool initEnd = false;

	// Retry button
	sf::RectangleShape retryButton;
	sf::Text retryText;
	retryText.setFont(titlefont);
	SetButton(retryButton, sf::Vector2f(screenResolution.x / 2 - screenResolution.x / 16, screenResolution.y / 2 + tailleButtonY + screenResolution.y / 30), sf::Vector2f(tailleButtonX, tailleButtonY), sf::Color::Black, sf::Color::White, retryText, "Retry", sf::Color::White, 40);

	// Player 1 score
		// "Joueur 1 score :"
	sf::Text scoreJ1FinalText;
	scoreJ1FinalText.setFont(titlefont);
	scoreJ1FinalText.setString("Joueur 1");
		// Actual score display
	sf::Text scoreJ1Final;
	scoreJ1Final.setFont(titlefont);

	// Player 2 score
		// "Joueur 2 score :"
	sf::Text scoreJ2FinalText;
	scoreJ2FinalText.setFont(titlefont);
	scoreJ2FinalText.setString("Joueur 2");
		// Actual score display
	sf::Text scoreJ2Final;
	scoreJ2Final.setFont(titlefont);
	#pragma endregion

	// Game loop
	while (window.isOpen()) {

		if(getState() == GameState::MENU)
		{
			#pragma region Main Menu loop
			// Inputs gestion
			#pragma region Inputs gestion
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) || isButtonPressed(quitButton.getPosition(), quitButton.getSize(), event.mouseButton.x, event.mouseButton.y)) {
					window.close();
				}
				if (event.mouseButton.button == sf::Mouse::Left && isButtonPressed(J1Button.getPosition(), J1Button.getSize(), event.mouseButton.x, event.mouseButton.y))
				{
					playerInGame = 1;
					playerTwo.isDead = true;
					setGameState(GameState::JEU);
				}
				if (event.mouseButton.button == sf::Mouse::Left && isButtonPressed(J2Button.getPosition(), J2Button.getSize(), event.mouseButton.x, event.mouseButton.y))
				{
					playerInGame = 2;
					isPlayerTwo = true;
					setGameState(GameState::JEU);
				}
			}
			#pragma endregion

			// Change colors of the buttons with time
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

			// Clear/Draw/Display window
			#pragma region Window gestion
			window.clear();

				// Title
			window.draw(titleText);
				// Play buttons and texts
			window.draw(J1Button);
			window.draw(J1Text);
			window.draw(J2Button);
			window.draw(J2Text);
				// Quit button and text
			window.draw(quitButton);
			window.draw(quitText);

			window.display();
			#pragma endregion
			#pragma endregion
		}
		else if(getState() == GameState::JEU)
		{
			#pragma region Game loop

			// Inputs gestion
			#pragma region Inputs gestion
			sf::Event event;
			while (window.pollEvent(event)) {

				// Close window
				if (event.type == sf::Event::Closed) {
					window.close();
				}

				// Players controls
				if(event.type == sf::Event::KeyPressed)
				{
					// Players color change
					if(event.key.code == sf::Keyboard::A)
					{
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
					if(event.key.code == sf::Keyboard::M)
					{
						playerColor2 = ChangeSide(playerColor2, 2);
						//bonus pour 1J
						bonus = BonusCrea1J(playerOne.player, circleGame);
						ChooseBonus(bonus, isShowed, timerBonus);
					}
				}
			}
			#pragma endregion

			// Restart clock to get elapsedTime == deltaTime
			sf::Time elapsedTime = clock.restart();

			// Set player colors
			playerOne.SetColors(playerColor);
			if (isPlayerTwo) playerTwo.SetColors(playerColor2);

			// Increase player score
			if (!playerOne.isDead) scoreJ1 = SetScore(scorePlayerOne.getElapsedTime().asSeconds(), scorePlayerOneText, 1, comboJ1, scoreJ1);
			if (!playerTwo.isDead && isPlayerTwo) scoreJ2 = SetScore(scorePlayerTwo.getElapsedTime().asSeconds(), scorePlayerTwoText, 2, comboJ2, scoreJ2);

			// Black hole gestion
			#pragma region Black hole gestion
				// Launch new attacks when current attack finished
			if(blackHole.attackTimer <= 0)
			{
				blackHole.LaunchNewAttack(&entities);
			}
			else
			{
				// Decrease the current attack timer
				blackHole.attackTimer = blackHole.attackTimer - elapsedTime.asSeconds();

				// Decrease the timer of the current attack's current wave --> if the timer below 0 --> new wave of the attack is launched
				blackHole.currentAttackPtr->waveTimer = blackHole.currentAttackPtr->waveTimer - elapsedTime.asSeconds();
				blackHole.currentAttackPtr->SpawnWaveIfFinished(*(blackHole.position), &entities);
			}
			#pragma endregion

			// Change world colors periodically
			if (timerColorChange.getElapsedTime().asSeconds() >= 10) {
			ChangeColorForEverything(playerColor, playerColor2, colorEntities, idC);
			timerColorChange.restart();
			}

			// Bonus gestion
			#pragma region Bonus gestion
			if (timerSpawnBonus.getElapsedTime().asSeconds() >= 8 && isPlayerTwo) {
				bonus = BonusCrea2J(playerOne.player, playerTwo.player, circleGame);
				float distancePlayers = (playerOne.player.getRotation() + playerTwo.player.getRotation()) / 2;
				if (distancePlayers <= 180.f) {
					bonus.setRotation(distancePlayers - 180.f);
				}
				else {
					bonus.setRotation(distancePlayers + 180.f);
				}
				ChooseBonus(bonus, isShowed, timerBonus);
				timerSpawnBonus.restart();
			}
			else if (timerSpawnBonus.getElapsedTime().asSeconds() >= 8 && !isPlayerTwo) {
				bonus = BonusCrea1J(playerOne.player, circleGame);
				ChooseBonus(bonus, isShowed, timerBonus);
				timerSpawnBonus.restart();
			}

			//Bonus Behavior
			if (bonus.getFillColor() == sf::Color::Red) {

				float rotationBonusMin = bonus.getRotation() - 5;
				float rotationBonusMax = bonus.getRotation() + 5;

				std::cout << "Bonus rotation : " << rotationBonusMin << ", " << rotationBonusMax << "[" << bonus.getRotation() << "]" << std::endl;
				std::cout << "Player rotation : " << playerOne.player.getRotation() + 180 << std::endl;
				if (playerOne.player.getRotation() <= 180) {
					std::cout << " - 180" << std::endl;
					if (playerOne.player.getRotation() + 180 <= rotationBonusMax && playerOne.player.getRotation() + 180 >= rotationBonusMin) {
						std::cout << "hit" << std::endl;
						playerOne.AdjustLife(1, &timerBonus);
						isShowed = false;
					}
				}
				else {
					if (playerOne.player.getRotation() - 180 <= rotationBonusMax && playerOne.player.getRotation() - 180 >= rotationBonusMin) {
						std::cout << "hit" << std::endl;
						playerOne.AdjustLife(1, &timerBonus);
						isShowed = false;
					}
				}
				if (playerTwo.player.getRotation() <= 180) {
					std::cout << " - 180" << std::endl;
					if (playerTwo.player.getRotation() + 180 <= rotationBonusMax && playerTwo.player.getRotation() + 180 >= rotationBonusMin) {
						std::cout << "hit" << std::endl;
						playerTwo.AdjustLife(1, &timerBonus);
						isShowed = false;
					}
				} else {
					if (playerTwo.player.getRotation() - 180 <= rotationBonusMax && playerTwo.player.getRotation() - 180 >= rotationBonusMin) {
						std::cout << "hit" << std::endl;
						playerTwo.AdjustLife(1, &timerBonus);
						isShowed = false;
					}
				}
			}
			#pragma endregion

			// Players deplacement
			if(playerOne.actualLife > 0) Deplacement(playerOne, elapsedTime);
			if(playerTwo.actualLife > 0 && isPlayerTwo) Deplacement(playerTwo, elapsedTime);

			// Change colors of players and projectiles periodically
			if (timerColorChange.getElapsedTime().asSeconds() >= 10) {
				ChangeColorForEverything(playerColor, playerColor2, colorEntities, idC);
				timerColorChange.restart();
			}

			window.clear();

			// Entities gestion (entities == projectiles)
			#pragma region Entities gestion
				// vectors meant to contain pointers of entities colliding with players
			std::vector<Entity*> touchingPlayer1;
			std::vector<Entity*> touchingPlayer2;

				// Big function moving, calculating new radius, drawing, checking collision with players, destroying entities too far
			HandleEntities(&entities, &window, middleScreen, circleRadius, elapsedTime.asSeconds(),
				Vector2::FromSFVector2f(CoordPlayer(playerOne.player, circleGame)),
				Vector2::FromSFVector2f(CoordPlayer(playerTwo.player, circleGame)),	
				20,	&touchingPlayer1, &touchingPlayer2, colorEntities
			);
			#pragma endregion

			// Collision checks
			#pragma region Collision with players check
			// Check if there is collider touching player 1
			if (!touchingPlayer1.empty() && playerOne.actualLife > 0)
			{
				// Handle collision --> Remove life, reset bonus...
				playerOne.OnCollisionWithEntities(&entities, touchingPlayer1, 
					playerColor, colorEntities, 
					comboJ1, timerComboJ1, &scorePlayerOne);
			}
			// Check if there is collider touching player 2
			if (!touchingPlayer2.empty() && playerTwo.actualLife > 0 && isPlayerTwo)
			{
				playerTwo.OnCollisionWithEntities(&entities, touchingPlayer2,
					playerColor2, colorEntities,
					comboJ2, timerComboJ2, &scorePlayerTwo);
			}
			#pragma endregion

			// Check if game finished
			if(playerInGame == 0)
			{
				setGameState(GameState::FIN);
				initEnd = false;
			}

			// Clear/Draw/Display
			#pragma region Window gestion

				// Circle path of the players
			window.draw(circleGame);

				// Draw entities
			//DrawEntities(&entities, &window, colorEntities);

				// Draw bonus
			if (timerBonus.getElapsedTime().asSeconds() >= 3) {
				isShowed = false;
			}
			if (isShowed) {
				window.draw(bonus);
			}

				// Draw players
					// Player 1
			if (playerOne.actualLife > 0)
				window.draw(playerOne.player);
			else if(!playerOne.isDead)
			{
				playerInGame--;
				playerOne.isDead = true;
			}
					// Player 2
			if(playerTwo.actualLife > 0 && isPlayerTwo)
				window.draw(playerTwo.player);
			else if(!playerTwo.isDead){
				playerInGame--;
				playerTwo.isDead = true;
			}

				//Display scores
			window.draw(scorePlayerOneText);
			if (isPlayerTwo) window.draw(scorePlayerTwoText);

				// Draw players lifes
			for (int i = 0; i < 3; i++)
			{
				window.draw(playerOne.tabLifeCircle[i]);
				if (isPlayerTwo)
					window.draw(playerTwo.tabLifeCircle[i]);
			}

			window.display();
			#pragma endregion

			#pragma endregion
		}
		else if (getState() == GameState::FIN)
		{
			#pragma region End menu loop

			if(!initEnd)
			{
				initEnd = true;
				quitButton.setPosition(quitButton.getPosition().x, quitButton.getPosition().y + tailleButtonY + screenResolution.y / 30);
				quitText.setPosition(quitButton.getPosition().x + (tailleButtonX / 2), quitButton.getPosition().y + (tailleButtonY / 2));
				setChangeColor(quitButton, quitText, sf::Color::Black, sf::Color::White);

				SetText(scoreJ1FinalText, 1, screenResolution.ToSFVector2f(), isPlayerTwo);
				SetText(scoreJ2FinalText, 2, screenResolution.ToSFVector2f(), isPlayerTwo);

				scoreJ1Final.setString(std::to_string((int)scoreJ1));
				scoreJ2Final.setString(std::to_string((int)scoreJ2));
				SetText(scoreJ1Final, 1, screenResolution.ToSFVector2f(), isPlayerTwo);
				SetText(scoreJ2Final, 2, screenResolution.ToSFVector2f(), isPlayerTwo);
				scoreJ1Final.setPosition(scoreJ1Final.getPosition().x, scoreJ1Final.getPosition().y + screenResolution.y / 24);
				scoreJ2Final.setPosition(scoreJ2Final.getPosition().x, scoreJ2Final.getPosition().y + screenResolution.y / 24);
			}


			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) || isButtonPressed(quitButton.getPosition(), quitButton.getSize(), event.mouseButton.x, event.mouseButton.y)) {
					window.close();
				}
			}


			window.clear();
			window.draw(quitButton);
			window.draw(quitText);

			window.draw(retryButton);
			window.draw(retryText);

			window.draw(scoreJ1FinalText);
			window.draw(scoreJ1Final);

			if(isPlayerTwo)
			{
				window.draw(scoreJ2FinalText);
				window.draw(scoreJ2Final);
			}

			window.display();
			#pragma endregion
		}
	}
}
