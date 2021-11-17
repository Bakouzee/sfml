#pragma once
#include <SFML/Graphics.hpp>
#include "Arthur.h"

enum Bonus {
	SLOW_DOWN,
	HEALTH_UP
};

void ChooseBonus(sf::CircleShape& bonus, bool& showBonus, sf::Clock& timerBonus);