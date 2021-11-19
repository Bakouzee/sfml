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
	bool speedUp = false;
	float comboJ1 = 1.f;
	float comboJ2 = 1.f;
	float scoreJ1 = 0.f;
	float scoreJ2 = 0.f;
	int playerCollide = -1;

	// Cercle du Jeu
	sf::CircleShape circleGame = CircleGameCrea(middleScreen.x, middleScreen.y);

	//Player
	int playerInGame = 0;
	bool isMultiplayer = false;
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
	sf::Clock timerSlowU;

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
	scoreJ1FinalText.setString("Player 1");

	sf::Text scoreJ1Final;
	scoreJ1Final.setFont(titlefont);

	// Player 2 score
		// "Joueur 2 score :"
	sf::Text scoreJ2FinalText;
	scoreJ2FinalText.setFont(titlefont);
	scoreJ2FinalText.setString("Player 2");

	sf::Text scoreJ2Final;
	scoreJ2Final.setFont(titlefont);

	sf::Text joueurXWinText;
	joueurXWinText.setFont(titlefont);

	sf::Text bestScore;
	bestScore.setFont(titlefont);
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
					isMultiplayer = true;
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
		else if (getState() == GameState::INIT)
		{
			#pragma region Init loop

			playerOne.player.setRotation(0);
			playerOne.isDead = false;
			playerOne.actualLife = 3;
			playerInGame++;
			scoreJ1 = 0;
			comboJ1 = 0.1;
			scorePlayerOne.restart();
			timerComboJ1.restart();
			scoreJ1 = SetScore(scorePlayerOne.getElapsedTime().asSeconds(), scorePlayerOneText, 1, comboJ1, scoreJ1);


			if(isMultiplayer)
			{
				playerTwo.player.setRotation(0);
				playerTwo.isDead = false;
				playerTwo.actualLife = 3;
				playerInGame++;
				scoreJ2 = 0;
				comboJ2 = 0.1;
				scorePlayerTwo.restart();
				timerComboJ2.restart();
				scoreJ2 = SetScore(scorePlayerTwo.getElapsedTime().asSeconds(), scorePlayerTwoText, 2, comboJ2, scoreJ2);
			}

			for (int i = 0; i < 3; i++)
			{
				playerOne.tabLifeCircle[i].setFillColor(sf::Color(180, 0, 0, 255));
				if (isMultiplayer)
					playerTwo.tabLifeCircle[i].setFillColor(sf::Color(180, 0, 0, 255));
			}

			clock.restart();
			timerBonus.restart();
			timerSpawnBonus.restart();
			timerColorChange.restart();

			entities.clear();

			setGameState(GameState::JEU);
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
					
					}
					if(event.key.code == sf::Keyboard::M)
					{
						playerColor2 = ChangeSide(playerColor2, 2);
					}
				}
			}
			#pragma endregion

			// Restart clock to get elapsedTime == deltaTime
			sf::Time elapsedTime = clock.restart();
			window.clear();

			// Set player colors
			playerOne.SetColors(playerColor);
			if (isMultiplayer) playerTwo.SetColors(playerColor2);

			// Increase player score
			if (!playerOne.isDead) scoreJ1 = SetScore(scorePlayerOne.getElapsedTime().asSeconds(), scorePlayerOneText, 1, comboJ1, scoreJ1);
			if (!playerTwo.isDead && isMultiplayer) scoreJ2 = SetScore(scorePlayerTwo.getElapsedTime().asSeconds(), scorePlayerTwoText, 2, comboJ2, scoreJ2);

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
			if (timerSpawnBonus.getElapsedTime().asSeconds() >= 8 && isMultiplayer) {
				bonus = BonusCrea2J(playerOne.player, playerTwo.player, circleGame);
				SetupPositionBonus2J(bonus, playerOne.player, playerTwo.player);
				ChooseBonus(bonus, playerOne, playerTwo, isMultiplayer, isShowed, timerBonus);
				timerSpawnBonus.restart();
			}
			if (timerSpawnBonus.getElapsedTime().asSeconds() >= 8 && !isMultiplayer) {
				bonus = BonusCrea1J(playerOne.player, circleGame);
				ChooseBonus(bonus, playerOne, playerTwo, !isMultiplayer, isShowed, timerBonus);
				timerSpawnBonus.restart();
			}

			if (timerBonus.getElapsedTime().asSeconds() >= 3 && isMultiplayer) {
				isShowed = false;
			}
			else if (timerBonus.getElapsedTime().asSeconds() >= 4 && !isMultiplayer) {
				isShowed = false;
			}
			if (isShowed) {
				CollideAndApplyBonus(bonus, playerOne, playerTwo, isMultiplayer, isShowed, timerBonus, speedUp, playerCollide);
				window.draw(bonus);
			}
			//SpeedUp for the adversary
			if (speedUp) {
				isShowed = false;
				std::cout << playerCollide << std::endl;
				if (playerCollide == 1) {
					playerTwo.speedPlayer = 150.f;
					timerSlowU.restart();
					playerCollide = -1;
				}
				if (playerCollide == 2){
					playerOne.speedPlayer = 150.f;
					timerSlowU.restart();
					playerCollide = -1;
				}
				if (timerSlowU.getElapsedTime().asSeconds() >= 2.f) {
					playerTwo.speedPlayer = 100.f;
					playerOne.speedPlayer = 100.f;
					speedUp = false;
				}
			}
			#pragma endregion

			if(!playerOne.isDead) Deplacement(playerOne, elapsedTime);
			if(!playerTwo.isDead && isMultiplayer) Deplacement(playerTwo, elapsedTime);

			// Change colors of players and projectiles periodically
			if (timerColorChange.getElapsedTime().asSeconds() >= 10) {
				ChangeColorForEverything(playerColor, playerColor2, colorEntities, idC);
				timerColorChange.restart();
			}

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
			if (!touchingPlayer1.empty() && !playerOne.isDead)
			{
				// Handle collision --> Remove life, reset bonus...
				playerOne.OnCollisionWithEntities(&entities, touchingPlayer1,
					playerColor, colorEntities,
					comboJ1, timerComboJ1, &scorePlayerOne);

				if (playerOne.isDead) playerInGame--;
			}
			// Check if there is collider touching player 2
			if (!touchingPlayer2.empty() && !playerTwo.isDead && isMultiplayer)
			{
				playerTwo.OnCollisionWithEntities(&entities, touchingPlayer2,
					playerColor2, colorEntities,
					comboJ2, timerComboJ2, &scorePlayerTwo);

				if (playerTwo.isDead) playerInGame--;
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
			if (!playerOne.isDead)
				window.draw(playerOne.player);
					// Player 2
			if(!playerTwo.isDead && isMultiplayer)
				window.draw(playerTwo.player);

				//Display scores
			window.draw(scorePlayerOneText);
			if (isMultiplayer) window.draw(scorePlayerTwoText);

				// Draw players lifes
			for (int i = 0; i < 3; i++)
			{
				window.draw(playerOne.tabLifeCircle[i]);
				if (isMultiplayer)
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
				quitButton.setPosition(screenResolution.x / 2 - screenResolution.x / 16, screenResolution.y / 2 + tailleButtonY + screenResolution.y / 30 + tailleButtonY + screenResolution.y / 30);
				quitText.setPosition(screenResolution.x / 2 - screenResolution.x / 16 + (tailleButtonX / 2), screenResolution.y / 2 + tailleButtonY + screenResolution.y / 30 + tailleButtonY + screenResolution.y / 30 + (tailleButtonY / 2));
				setChangeColor(quitButton, quitText, sf::Color::Black, sf::Color::White);

				SetText(scoreJ1FinalText, 1, screenResolution.ToSFVector2f(), isMultiplayer);
				SetText(scoreJ2FinalText, 2, screenResolution.ToSFVector2f(), isMultiplayer);

				scoreJ1Final.setString(std::to_string((int)scoreJ1));
				scoreJ2Final.setString(std::to_string((int)scoreJ2));

				if (scoreJ1 > scoreJ2)
					joueurXWinText.setString("Player 1 won");
				else
					joueurXWinText.setString("Player 2 won");

				SetText(joueurXWinText, 0, screenResolution.ToSFVector2f(), isMultiplayer);

				if(GetBestScore() < scoreJ1)
					SetBestScore(scoreJ1);
				else if(GetBestScore() < scoreJ2)
					SetBestScore(scoreJ2);

				bestScore.setString("Best Score\n " + std::to_string(GetBestScore()));
				SetText(bestScore, 3, screenResolution.ToSFVector2f());


				SetText(scoreJ1Final, 1, screenResolution.ToSFVector2f(), isMultiplayer);
				SetText(scoreJ2Final, 2, screenResolution.ToSFVector2f(), isMultiplayer);
				scoreJ1Final.setPosition(scoreJ1Final.getPosition().x, scoreJ1Final.getPosition().y + screenResolution.y / 24);
				scoreJ2Final.setPosition(scoreJ2Final.getPosition().x, scoreJ2Final.getPosition().y + screenResolution.y / 24);
			}


			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) || isButtonPressed(quitButton.getPosition(), quitButton.getSize(), event.mouseButton.x, event.mouseButton.y)) {
					window.close();
				}
				else if (isButtonPressed(retryButton.getPosition(), retryButton.getSize(), event.mouseButton.x, event.mouseButton.y)) {
					setGameState(GameState::INIT);
				}
			}


			window.clear();
			window.draw(quitButton);
			window.draw(quitText);

			window.draw(retryButton);
			window.draw(retryText);

			window.draw(scoreJ1FinalText);
			window.draw(scoreJ1Final);

			window.draw(bestScore);


			if(isMultiplayer)
			{
				window.draw(joueurXWinText);
				window.draw(scoreJ2FinalText);
				window.draw(scoreJ2Final);
			}

			window.display();
			#pragma endregion
		}
	}
}
