#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

enum Bonus {
	SLOW_DOWN,
	HEALTH_UP
};

sf::CircleShape SpawnBonus(sf::CircleShape bonus, bool& showBonus, sf::Clock& timerBonus);