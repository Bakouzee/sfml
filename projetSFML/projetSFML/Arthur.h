#pragma once

struct Player
{
	int numberPlayer;
	sf::CircleShape player;
	int actualLife;
	sf::CircleShape tabLifeCircle[3];
};

const float PI = 3.14159265358979323846;
const float circleRadius = 200.0f;
const float playerRadius = 20.0f;

void Deplacement(Player& actualPlayer, sf::Time elapsedTime);

sf::Vector2f CoordPlayer(sf::CircleShape& player, sf::CircleShape circleGame);

sf::CircleShape CircleGameCrea(float positionX, float positionY);
sf::CircleShape PlayerCrea(sf::CircleShape circleGame);
Player NewPlayer(sf::CircleShape shape, int life, int number);
sf::CircleShape BonusCrea(sf::CircleShape circleGame);

void setLife(Player& actualPlayer, int lifeChange);
sf::CircleShape lifeCircle();
void SetPositionLifeCircle(Player& actualPlayer, float circleLifeRadius, float screenResolutionX);


////PURE TESTING POUR AFFICHER LES COORD // A METTRE DANS LE MAIN SI BESOIN
//sf::Font test;
//test.loadFromFile(getAssetPath() + "PIXEAB__.TTF");
//sf::Text affichage;
//affichage.setFont(test);
//affichage.setPosition(100, 50);
//
////Donne les coord du Player en tant r�el //A METTRE DANS LA BOUCLE
//affichage.setString(std::to_string(CoordPlayer(player, circleGame).x) + " / " + std::to_string(CoordPlayer(player, circleGame).y));
