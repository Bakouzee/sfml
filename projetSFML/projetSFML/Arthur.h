#pragma once


const float PI = 3.14159265358979323846;
const float circleRadius = 200.0f;

void Deplacement(sf::CircleShape& player, sf::Time elapsedTime);

sf::Vector2f CoordPlayer(sf::CircleShape& player, sf::CircleShape circleGame);

sf::CircleShape CircleGameCrea(float positionX, float positionY);
sf::CircleShape PlayerCrea(float radius, sf::CircleShape circleGame);


////PURE TESTING POUR AFFICHER LES COORD // A METTRE DANS LE MAIN SI BESOIN
//sf::Font test;
//test.loadFromFile(getAssetPath() + "PIXEAB__.TTF");
//sf::Text affichage;
//affichage.setFont(test);
//affichage.setPosition(100, 50);
//
////Donne les coord du Player en tant réel //A METTRE DANS LA BOUCLE
//affichage.setString(std::to_string(CoordPlayer(player, circleGame).x) + " / " + std::to_string(CoordPlayer(player, circleGame).y));