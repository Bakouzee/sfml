#pragma once

const float PI = 3.14159265358979323846;
const float circleRadius = 425.0f;
const float playerRadius = 25.0f;

struct Player
{
	int numberPlayer;
	sf::CircleShape player;
	int actualLife;
	float speedPlayer = 100;
	sf::ConvexShape tabLifeCircle[3];
	int scorePlayer = 0;
	bool isDead = false;
};

enum GameState
{
	MENU,
	JEU,
	FIN,
	INIT
};

//GameManager.cpp
void setGameState(GameState actualState);
GameState getState();

//SetupMenu.cpp
bool isButtonPressed(sf::Vector2f position, sf::Vector2f size, int mousePositionX, int mousePositionY);
void SetButton(sf::RectangleShape& button, sf::Vector2f positionButton, sf::Vector2f sizeButton, sf::Color colorButton, sf::Color colorButtonThick, sf::Text& textButton, sf::String texte, sf::Color colorText, int sizeText);
void changeColor(int& actualColor, sf::Color& color1, sf::Color& color2);
void setChangeColor(sf::RectangleShape& button, sf::Text& textButton, sf::Color color1, sf::Color color2);
void setTitle(sf::Text& titleText, sf::Vector2<float> screenResolution);

//Deplacement.cpp
void Deplacement(Player& actualPlayer, sf::Time elapsedTime);
sf::Vector2f CoordPlayer(sf::CircleShape& player, sf::CircleShape circleGame);

//SetupDeplacement.cpp
sf::CircleShape CircleGameCrea(float positionX, float positionY);
sf::CircleShape PlayerCrea(sf::CircleShape circleGame, int whatPlayer);
Player NewPlayer(sf::CircleShape shape, int life, int number);

//Health.cpp
void setLife(Player& actualPlayer, int lifeChange, sf::Clock clockPlayer);
sf::ConvexShape lifeCircle();
void SetPositionLifeCircle(Player& actualPlayer, float circleLifeRadius, float screenResolutionX);

//ScoreManager.cpp
void SetText(sf::Text& actualText, int numberPlayer, sf::Vector2f screenResolution, bool isPlayerTwoActive = false);
float SetScore(float actualTime, sf::Text& actualText, int numberPlayer, float combo, float score);




////PURE TESTING POUR AFFICHER LES COORD // A METTRE DANS LE MAIN SI BESOIN
//sf::Font test;
//test.loadFromFile(getAssetPath() + "PIXEAB__.TTF");
//sf::Text affichage;
//affichage.setFont(test);
//affichage.setPosition(100, 50);
//
////Donne les coord du Player en tant r�el //A METTRE DANS LA BOUCLE
//affichage.setString(std::to_string(CoordPlayer(player, circleGame).x) + " / " + std::to_string(CoordPlayer(player, circleGame).y));