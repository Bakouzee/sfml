#include <SFML/Graphics.hpp>
#include "windows.h"
#include <iostream>

std::string getAppPath() {
	char cExeFilePath[256];
	GetModuleFileNameA(NULL, cExeFilePath, 256);
	std::string exeFilePath = cExeFilePath;
	int exeNamePos = exeFilePath.find_last_of("\\/");
	std::string appPath = exeFilePath.substr(0, exeNamePos + 1);
	return appPath;
}

std::string getAssetPath() {
	return getAppPath() + "\\Assets";
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "ChronoSpacer");
	// Initialise everything below
	 
	
	// Game loop
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			// Process any input event here
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && sf::Keyboard::Escape)) {
				window.close();
			}
		}
		window.clear();
		// Whatever I want to draw goes here
		window.display();
	}
}

