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

void Entity::Move(float& deltaTime)
{
	
	*position += *direction * currentSpeed * deltaTime;
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
	this->currentRadius = this->radiusMinMax.min;
}

std::string Entity::to_string()
{
	return "Entity = { pos: " + position->ToString() + "; dir = " + direction->ToString() + "; primaryColor: " + std::to_string(primaryColor) + "currentRadius: " + std::to_string(currentRadius) + " }";
}


#pragma endregion

#pragma region Entities

#pragma region Deprected
//void DrawEntities(std::list<Entity>* entitiesPtr, sf::RenderWindow* windowPtr)
//{
//	sf::CircleShape circle(0.5f);
//	for (Entity entity : *entitiesPtr)
//	{
//		float radius = entity.GetRadius();
//		circle.setRadius(std::round(radius));
//
//		circle.setOrigin(radius, radius);
//
//		sf::Vector2f position(entity.position->x, entity.position->y);
//		circle.setPosition(position);
//
//		windowPtr->draw(circle);
//	}
//}
//void MoveEntities(std::list<Entity>* entitiesPtr, float deltaTime)
//{
//	for (Entity entity : *entitiesPtr)
//	{
//		if (entity.position->IsZero()) continue;
//		entity.Move(deltaTime);
//	}
//}
//bool CheckCollisions(Vector2 pos, float radius, std::list<Entity>* entitiesPtr, std::vector<Entity*>* collidingEntities)
//{
//	bool hasCollision = false;
//
//	for (auto it = entitiesPtr->begin(); it != entitiesPtr->end(); ++it)
//	{
//		Vector2 entityPos = *((*it).position);
//		if (Vector2::GetDistance(pos, entityPos) < radius + it->GetRadius())
//		{
//			// Collision
//			if (!hasCollision) hasCollision = true;
//
//			collidingEntities->push_back(&(*it));
//		}
//	}
//
//	return hasCollision;
//}

// Breaking the game --> probably infinity loop
//void DestroyEntities(std::vector<Entity*>* toDeleteEntities, std::list<Entity>* entitiesPtr)
//{
//	// Loop in the entities
//	auto it = entitiesPtr->begin();
//	while (it != entitiesPtr->end())
//	{
//		bool deleted = false;
//
//		// Check if we want to delete it
//		auto it2 = toDeleteEntities->begin();
//		while(it2 != toDeleteEntities->end())
//		{
//			// Found
//			if (*it2 == &(*it))
//			{
//				it = entitiesPtr->erase(it);
//				//it2 = toDeleteEntities->erase(it2);
//				deleted = true;
//				break;
//			}
//		}
//
//		if(!deleted) it++;
//	}
//}
//void DestroyFarEntities(Vector2 middle, float minDistance, std::list<Entity>* entitiesPtr)
//{
//	auto it = entitiesPtr->begin();
//	while(it != entitiesPtr->end())
//	{
//		if (Vector2::GetDistance(middle, *it->position) >= minDistance)
//		{
//			it = entitiesPtr->erase(it);
//		}
//		else it++;
//	}
//}
#pragma endregion

void Entity::CalculateCurrantRadius(Vector2& gameCenter, float& gameRadius)
{
	float t = std::min(gameRadius, Vector2::GetDistance(*position, gameCenter)) / gameRadius;

	if (t >= 1) currentRadius = radiusMinMax.max;
	else currentRadius = radiusMinMax.min + (radiusMinMax.max - radiusMinMax.min) * t;
}
void DrawEntity(Entity* entityPtr, sf::RenderWindow* windowPtr, Colors& colors)
{
	float entityRadius = entityPtr->currentRadius;

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
void MoveEntity(Entity* entityPtr, float deltaTime)
{
	if (entityPtr->direction->IsZero()) return;
	entityPtr->Move(deltaTime);
}
bool IsInCollisionWithPlayer(Entity* entityPtr, Vector2& playerPos, float& playerRadius)
{
	return Vector2::GetDistance(*entityPtr->position, playerPos) <= playerRadius + entityPtr->currentRadius;
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

		// Set Entity current radius
		entityPtr->CalculateCurrantRadius(gameCenter, gameRadius);

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
		else
		{
			// Continue entity update

			// Move entity
			MoveEntity(entityPtr, deltaTime);

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

//std::ostream& operator<<(std::ostream& os, const Entity entity)
//{
//	os << "Entity = { pos: " /*<< entity.position << "; dir: " << entity.direction */ << "; primaryColor: " << entity.primaryColor << "currentRadius: " << const_cast<Entity&>(entity).GetRadius() << " }";
//	return os;
//}

