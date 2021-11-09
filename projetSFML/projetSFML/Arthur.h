#pragma once


const float PI = 3.14159265358979323846;
const float circleRadius = 200.0f;

void Deplacement(sf::CircleShape& player, sf::Time elapsedTime);

sf::Vector2f CoordPlayer(sf::CircleShape& player, sf::CircleShape circleGame);

sf::CircleShape CircleGameCrea(float position);
sf::CircleShape PlayerCrea(float radius, sf::CircleShape circleGame);




////MAIN ARTHUR
//int main()
//{
//	sf::RenderWindow window(sf::VideoMode(800, 600), "UnJeuDeMalade");
//	window.setVerticalSyncEnabled(true);
//
//	// Initialise everything below
//
//	// Cercle du Jeu
//	sf::CircleShape circleGame = CircleGameCrea(300);
//
//	//Actuel Player
//	sf::CircleShape player = PlayerCrea(20, circleGame);
//
//	// Clock
//	sf::Clock clock;
//
//	//PURE TESTING POUR AFFICHER LES COORD
//	sf::Font test;
//	test.loadFromFile(getAssetPath() + "PIXEAB__.TTF");
//	sf::Text affichage;
//	affichage.setFont(test);
//	affichage.setPosition(100, 50);
//
//	// Game loop
//	while (window.isOpen()) {
//
//		// Clock
//		sf::Time elapsedTime = clock.restart(); // elapsedTime.asSeconds() pour l'utiliser
//
//		// Process any input event here
//		sf::Event event;
//		while (window.pollEvent(event)) {
//			if (event.type == sf::Event::Closed) {
//				window.close();
//			}
//
//			Deplacement(player, elapsedTime);
//		}
//
//		//Donne les coord du Player en tant réel
//		affichage.setString(std::to_string(CoordPlayer(player, circleGame).x) + " / " + std::to_string(CoordPlayer(player, circleGame).y));
//
//		// Whatever I want to draw goes here
//		window.clear();
//
//		//Affichage
//		window.draw(circleGame);
//		window.draw(player);
//		window.draw(affichage);
//
//		window.display();
//	}
//}