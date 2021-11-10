#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

enum Bonus {
	SLOW_DOWN,
	HEALTH_UP
};

void SpawnBonus();