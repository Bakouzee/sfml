#pragma once
#include <iostream>
#include "2D.h"
#include <SFML/Graphics.hpp>

struct MinMax
{
	float min;
	float max;
};

struct Entity
{
public:
	Vector2 position;
	Vector2 direction;

	bool primaryColor;

	float GetRadius()
	{
		const float distanceForMaxScale = 5.0;
		const Vector2 middleScreen = { 480, 480 };

		float t = std::min(distanceForMaxScale, GetDistance(position, middleScreen)) / distanceForMaxScale;
		if (t >= 1) return radius.max;

		return radius.min + (radius.max - radius.min) * t;
	}

	Entity(Vector2 pos, Vector2 dir, bool primaryColor, MinMax radius)
	{
		position = pos;
		direction = dir;
		this->primaryColor = primaryColor;
		this->radius = radius;

		
	}

	void Log()
	{
		std::cout << "Entity = { pos: " << position.ToString() << "; dir: " << direction.ToString() << "; primaryColor: " << primaryColor << "currentRadius: " << GetRadius() << " }" << std::endl;
	}

private:
	MinMax radius;
};