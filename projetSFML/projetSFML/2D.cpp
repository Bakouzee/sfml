#pragma once
#include <iostream>
#include "2D.h"

float GetDistance(Vector2 a, Vector2 b)
{
	return std::sqrt((b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y));
}