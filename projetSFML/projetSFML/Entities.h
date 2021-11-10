#pragma once
#include <list>
#include "2D.h"
#include "Colors.h"

///	How to use Entities:
///	Create a container of entities
///	Add/Remove all wanted entities of this container
///
/// Use HandleEntities function to Draw, Move, Delete if too far from a point, and Detect collision
/// with a circle for each entities


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

	float currentSpeed;
	void MultiplySpeed(float multiplier);
	void ResetSpeed();

	bool primaryColor;
	void SetColors(Colors newColors);

	MinMax radiusMinMax;
	float currentRadius;
	void CalculateCurrantRadius(Vector2& gameCenter, float& gameRadius);

	void Move(float& deltaTime);

	Entity(Vector2 pos, Vector2 dir, float speed, bool primaryColor, MinMax radius);

	std::string to_string();

private:
	// Colors colors;
	float normalSpeed;

	Colors currentColors;
};

//std::ostream& operator<<(std::ostream& os, const Entity entity);

//void DrawEntities(std::list<Entity>* entitiesPtr, sf::RenderWindow* windowPtr);
//void MoveEntities(std::list<Entity>* entitiesPtr, float deltaTime);
//bool CheckCollisions(Vector2 pos, float radius, std::list<Entity>* entitiesPtr, std::vector<Entity*>* collidingEntities);
//void DestroyEntities(std::vector<Entity*>* toDeleteEntities, std::list<Entity>* entitiesPtr);
//void DestroyFarEntities(Vector2 middle, float minDistance, std::list<Entity>* entitiesPtr);

void DrawEntity(Entity* entityPtr, sf::RenderWindow* windowPtr, Colors& colors);
void MoveEntity(Entity* entityPtr, float deltaTime);
bool IsInCollisionWithPlayer(Entity* entityPtr, Vector2& playerPos, float& playerRadius);
void DestroyEntity(Entity* toDeleteEntity, std::list<Entity>* entitiesPtr);
void HandleEntities(std::list<Entity>* entities, sf::RenderWindow* windowPtr, Vector2 gameCenter, float gameRadius, float deltaTime,
	Vector2 player1Pos, Vector2 player2Pos, float playerRadius,  
	std::vector<Entity*>* entitiesTouchingPlayer1, std::vector<Entity*>* entitiesTouchingPlayer2,
	Colors& colors);
