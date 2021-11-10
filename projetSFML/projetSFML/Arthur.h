#pragma once


const float PI = 3.14159265358979323846;
const float circleRadius = 200.0f;
const float playerRadius = 20.0f;

void Deplacement(sf::CircleShape& player, sf::Time elapsedTime);

sf::Vector2f CoordPlayer(sf::CircleShape& player, sf::CircleShape circleGame);

sf::CircleShape CircleGameCrea(float positionX, float positionY);
sf::CircleShape PlayerCrea(sf::CircleShape circleGame);
sf::CircleShape BonusCrea(sf::CircleShape circleGame);

int setLife(int actualLife, int lifeChange, sf::CircleShape tabLifeCircle[]);
sf::CircleShape lifeCircle();
void SetPositionLifeCircle(sf::CircleShape tabLifeCircle[], float circleLifeRadius);


////PURE TESTING POUR AFFICHER LES COORD // A METTRE DANS LE MAIN SI BESOIN
//sf::Font test;
//test.loadFromFile(getAssetPath() + "PIXEAB__.TTF");
//sf::Text affichage;
//affichage.setFont(test);
//affichage.setPosition(100, 50);
//
////Donne les coord du Player en tant réel //A METTRE DANS LA BOUCLE
//affichage.setString(std::to_string(CoordPlayer(player, circleGame).x) + " / " + std::to_string(CoordPlayer(player, circleGame).y));


			/*else if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::L))
			{
			life = setLife(life, 1, tabLifeCircle);
			}*/

//			//Point de vie Affichage
//sf::CircleShape tabLifeCircle[3] = { lifeCircle(), lifeCircle(), lifeCircle() };
//SetPositionLifeCircle(tabLifeCircle, 20);
////TEMPORAIRE
//int life = 3;