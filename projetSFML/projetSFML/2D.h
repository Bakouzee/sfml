#pragma once
#include <string>

struct Vector2
{
public:
	float x;
	float y;

	std::string ToString() {
		return "{" + std::to_string(x) + ", " + std::to_string(y) + "}";
	}
};

float GetDistance(Vector2 a, Vector2 b);
