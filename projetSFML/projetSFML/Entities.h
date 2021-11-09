#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include "2D.h"

struct MinMax
{
	float min;
	float max;

	::MinMax& operator=(MinMax minMax);

	MinMax();
	MinMax(float min, float max);
};

struct Entity
{
public:
	Vector2* position;
	Vector2* direction;

	bool primaryColor;

	float GetRadius();

	void Move(float& deltaTime);

	Entity(Vector2 pos, Vector2 dir, bool primaryColor, MinMax radius);

	std::string to_string();

private:
	MinMax radius;
};

//std::ostream& operator<<(std::ostream& os, const Entity entity);

void DrawEntities(std::list<Entity>* entitiesPtr, sf::RenderWindow* windowPtr);
void MoveEntities(std::list<Entity>* entitiesPtr, float deltaTime);
