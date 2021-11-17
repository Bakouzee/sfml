#include <SFML/Graphics.hpp>
#include "windows.h"
#include <iostream>
#include <list>
#include <vector>

#include "Colors.h"

#include "Arthur.h"
#include "2D.h"
#include "Entities.h"
#include "BlackHole.h"

#include "Bonus.h"
#include "Gamefeel.h"



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
	sf::RenderWindow window(sf::VideoMode(screenResolution.x, screenResolution.y), "Mega Black Hole");
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
	//sf::VertexArray tabGradient(sf::LinesStrip, 360);
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

	//sf::Clock timer;

	//Bonus
	sf::CircleShape bonus;
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

	// Game loop
	while (window.isOpen()) {
		//R�initialise la couleur du player
		playerOne.player.setFillColor(playerColor.primary);
		playerOne.player.setOutlineColor(playerColor.secondary);
		playerTwo.player.setFillColor(playerColor2.primary);
		playerTwo.player.setOutlineColor(playerColor2.secondary);

		// Clock
		sf::Time elapsedTime = clock.restart(); // elapsedTime.asSeconds() pour l'utiliser
		if(playerOne.actualLife > 0)
		{
			scoreJ1 = SetScore(scorePlayerOne.getElapsedTime().asSeconds(), scorePlayerOneText, 1, comboJ1, scoreJ1);
		}
		if (playerTwo.actualLife > 0)
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
				//newBonus = SpawnBonus(bonus, isShowed, timerBonus);
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M) {
				playerColor2 = ChangeSide(playerColor2, 2);
				//bonus pour 1J
				bonus = BonusCrea1J(playerOne.player, circleGame);
				ChooseBonus(bonus, isShowed, timerBonus);

				//newBonus = SpawnBonus(bonus, isShowed, timerBonus);
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


		//Distance à calculer entre la position du joueur et la position du bonus!!!!
		if (bonus.getFillColor() == sf::Color::Red){
			
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

			}

			
		}
		else if (bonus.getFillColor() == sf::Color::Red && ((int)playerTwo.player.getRotation() - (int)bonus.getRotation()) <= 5) {
			std::cout << "hit" << std::endl;
			setLife(playerTwo, 1, timerBonus);
			isShowed = false;
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
			window.draw(bonus);
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
					comboJ1 = 0.f;
				}
				else {
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
				}
				else {
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
		if(playerOne.actualLife > 0) window.draw(playerOne.player);
		if(playerTwo.actualLife > 0) window.draw(playerTwo.player);

		for (int i = 0; i < 3; i++)
		{
			window.draw(playerOne.tabLifeCircle[i]);
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
		window.display();
	}
}
