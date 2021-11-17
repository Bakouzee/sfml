#pragma once
#include "Entities.h"
#include <iostream>

#pragma region MinMax
MinMax& MinMax::operator=(MinMax minMax)
{
	min = minMax.min;
	max = minMax.max;
	return *this;
}

MinMax::MinMax()
{
	min = 0;
	max = 0;
}

MinMax::MinMax(float min, float max)
{
	this->min = min;
	this->max = max;
}
#pragma endregion

#pragma region Entity struct
void Entity::MultiplySpeed(float multiplier)
{
	currentSpeed = normalSpeed * multiplier;
}

void Entity::ResetSpeed()
{
	currentSpeed = normalSpeed;
}

void Entity::Move(float& deltaTime, float gameRadius)
{
	*position += *direction * currentSpeed * gameRadius * deltaTime;
}

Entity::Entity(Vector2 pos, Vector2 dir, float speed, bool primaryColor, MinMax radiusMinMax)
{
	position = new Vector2(pos.x, pos.y);

	direction = new Vector2(dir.x, dir.y);
	*direction = direction->Normalize();

	this->normalSpeed = speed;
	currentSpeed = speed;

	this->primaryColor = primaryColor;

	this->radiusMinMax = MinMax(radiusMinMax.min, radiusMinMax.max);
	this->currentPixelRadius = this->radiusMinMax.min;
}

std::string Entity::to_string()
{
	return "Entity = { pos: " + position->ToString() + "; dir = " + direction->ToString() + "; primaryColor: " + std::to_string(primaryColor) + "currentRadius: " + std::to_string(currentPixelRadius) + " }";
}


#pragma endregion

#pragma region Entities

void Entity::UpdateCurrentPixelRadius(Vector2& gameCenter, float& gameRadius)
{
	float t = std::min(gameRadius, Vector2::GetDistance(*position, gameCenter)) / gameRadius;

	if (t >= 1) currentPixelRadius = radiusMinMax.max;
	else currentPixelRadius = radiusMinMax.min + (radiusMinMax.max - radiusMinMax.min) * t;

	currentPixelRadius *= gameCenter.x * 2 / 1920;
}
void DrawEntity(Entity* entityPtr, sf::RenderWindow* windowPtr, Colors& colors)
{
	float entityRadius = entityPtr->currentPixelRadius;

	// Set circle shape
	sf::CircleShape circle(entityRadius);
	circle.setOrigin(entityRadius, entityRadius);

	// Set pos
	sf::Vector2f position(entityPtr->position->x, entityPtr->position->y);
	circle.setPosition(position);

	// Set color
	circle.setFillColor(entityPtr->primaryColor ? colors.primary : colors.secondary);
	circle.setOutlineColor(!entityPtr->primaryColor ? colors.primary : colors.secondary);
	circle.setOutlineThickness(1);

	// Draw
	windowPtr->draw(circle);
}
void DestroyEntity(Entity* toDeleteEntity, std::list<Entity>* entitiesPtr)
{
	auto it = entitiesPtr->begin();
	while(it != entitiesPtr->end())
	{
		if (toDeleteEntity == &(*it))
		{
			entitiesPtr->erase(it);
			return;
		}
		else it++;
	}
}
void MoveEntity(Entity* entityPtr, float deltaTime, float gameRadius)
{
	if (entityPtr->direction->IsZero()) return;
	entityPtr->Move(deltaTime, gameRadius);
}
bool IsInCollisionWithPlayer(Entity* entityPtr, Vector2& playerPos, float& playerRadius)
{
	return Vector2::GetDistance(*entityPtr->position, playerPos) <= playerRadius + entityPtr->currentPixelRadius;
}

void HandleEntities(std::list<Entity>* entities, sf::RenderWindow* windowPtr, Vector2 gameCenter, float gameRadius, float deltaTime,
	Vector2 player1Pos, Vector2 player2Pos, float playerRadius,
	std::vector<Entity*>* entitiesTouchingPlayer1, std::vector<Entity*>* entitiesTouchingPlayer2,
	Colors& colors)
{
	auto it = entities->begin();
	while(it != entities->end())
	{
		Entity* entityPtr = &(*it);

		// Update entity pixel radius
		entityPtr->UpdateCurrentPixelRadius(gameCenter, gameRadius);

		// Draw entity
		DrawEntity(entityPtr, windowPtr, colors);

		// Check if too far --> destroy
		// else continue the entity update
		if (Vector2::GetDistance(*(entityPtr->position), gameCenter) >= gameRadius)
		{
			// Destroy
			//std::cout << *(entityPtr->position) << " " << gameCenter << "too far so destroyed: " << Vector2::GetDistance(*entityPtr->position, gameCenter)  << std::endl;
			it = entities->erase(it);
		}
		
		else // Continue entity update
		{

			// Move entity
			MoveEntity(entityPtr, deltaTime, gameRadius);

			// Check if entity enter in collision with player 1
			if(IsInCollisionWithPlayer(entityPtr, player1Pos, playerRadius))
			{
				// Add it to the entities touching player 1 output
				entitiesTouchingPlayer1->push_back(entityPtr);
			}

			// Check if entity enter in collision with player 2
			if(IsInCollisionWithPlayer(entityPtr, player2Pos, playerRadius))
			{
				// Add it to the entities touching player 2 output
				entitiesTouchingPlayer2->push_back(entityPtr);
			}

			it++;
		}
	}
}
#pragma endregion