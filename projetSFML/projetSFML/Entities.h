#pragma once
#include <list>
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
	// SetColors(newColors)

	float GetRadius();

	void Move(float& deltaTime);

	Entity(Vector2 pos, Vector2 dir, bool primaryColor, MinMax radius);

	std::string to_string();

private:
	// Colors colors;
	MinMax radius;
};

//std::ostream& operator<<(std::ostream& os, const Entity entity);

// General


//void DrawEntities(std::list<Entity>* entitiesPtr, sf::RenderWindow* windowPtr);
//void MoveEntities(std::list<Entity>* entitiesPtr, float deltaTime);
//bool CheckCollisions(Vector2 pos, float radius, std::list<Entity>* entitiesPtr, std::vector<Entity*>* collidingEntities);
//void DestroyEntities(std::vector<Entity*>* toDeleteEntities, std::list<Entity>* entitiesPtr);
//void DestroyFarEntities(Vector2 middle, float minDistance, std::list<Entity>* entitiesPtr);

void DrawEntity(Entity* entityPtr, sf::RenderWindow* windowPtr);
void MoveEntity(Entity* entityPtr, float deltaTime);
bool IsInCollisionWithPlayer(Entity* entityPtr, Vector2& playerPos, float& playerRadius);
void DestroyEntity(Entity* toDeleteEntity, std::list<Entity>* entitiesPtr);
void HandleEntities(std::list<Entity>* entities, sf::RenderWindow* windowPtr, Vector2 gameCenter, float gameRadius, Vector2 playerPos, float playerRadius, float deltaTime, std::vector<Entity*>* entitiesTouchingPlayer);
