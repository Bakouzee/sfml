#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Arthur.h"

enum Bonus {
	SLOW_DOWN,
	HEALTH_UP
};

void ChooseBonus(Player& playerCollide, sf::CircleShape& bonus, bool& showBonus, sf::Clock& timerBonus);