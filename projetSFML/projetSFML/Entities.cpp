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
float Entity::GetRadius()
{
	float distanceForMaxScale = 200;
	Vector2 middleScreen = { 400, 300 };

	float t;
	t = std::min(distanceForMaxScale, Vector2::GetDistance(*position, middleScreen)) / distanceForMaxScale;
	if (t >= 1) return radius.max;

	return radius.min + (radius.max - radius.min) * t;
}

void Entity::Move(float& deltaTime)
{
	*position += *direction * deltaTime;
}

Entity::Entity(Vector2 pos, Vector2 dir, bool primaryColor, MinMax radiusMinMax)
{
	position = new Vector2(pos.x, pos.y);
	direction = new Vector2(dir.x, dir.y);
	this->primaryColor = primaryColor;
	radius = MinMax(radiusMinMax.min, radiusMinMax.max);
}

std::string Entity::to_string()
{
	return "Entity = { pos: " + position->ToString() + "; dir = " + direction->ToString() + "; primaryColor: " + std::to_string(primaryColor) + "currentRadius: " + std::to_string(GetRadius()) + " }";
}

#pragma endregion

#pragma region Entities
void DrawEntities(std::list<Entity>* entitiesPtr, sf::RenderWindow* windowPtr)
{
	sf::CircleShape circle(0.5f);
	for (Entity entity : *entitiesPtr)
	{
		float radius = entity.GetRadius();
		circle.setRadius(std::round(radius));

		circle.setOrigin(radius, radius);

		sf::Vector2f position(entity.position->x, entity.position->y);
		circle.setPosition(position);

		windowPtr->draw(circle);
	}
}

void MoveEntities(std::list<Entity>* entitiesPtr, float deltaTime)
{
	for (Entity entity : *entitiesPtr)
	{
		if (entity.position->IsZero()) continue;
		entity.Move(deltaTime);
	}
}

bool CheckCollisions(Vector2 pos, float radius, std::list<Entity>* entitiesPtr, std::vector<Entity*>* collidingEntities)
{
	bool hasCollision = false;

	for (auto it = entitiesPtr->begin(); it != entitiesPtr->end(); ++it)
	{
		Vector2 entityPos = *((*it).position);
		if (Vector2::GetDistance(pos, entityPos) < radius + it->GetRadius())
		{
			// Collision
			if (!hasCollision) hasCollision = true;

			collidingEntities->push_back(&(*it));
		}
	}

	return hasCollision;
}

void DestroyEntities(std::vector<Entity*>* toDeleteEntities, std::list<Entity>* entitiesPtr)
{
	// Loop in the entities
	auto it = entitiesPtr->begin();
	while (it != entitiesPtr->end())
	{
		bool deleted = false;

		// Check if we want to delete it
		auto it2 = toDeleteEntities->begin();
		while(it2 != toDeleteEntities->end())
		{
			// Found
			if (*it2 == &(*it))
			{
				it = entitiesPtr->erase(it);
				toDeleteEntities->erase(it2);
				deleted = true;
				break;
			}
		}

		if(!deleted) it++;
	}
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
void DestroyFarEntities(Vector2 middle, float minDistance, std::list<Entity>* entitiesPtr)
{
	std::vector<Entity*> toDeleteEnemies;

	auto it = entitiesPtr->begin();
	while(it != entitiesPtr->end())
	{
		if(Vector2::GetDistance(middle, *it->position) >= minDistance)
		{
			toDeleteEnemies.push_back(&(*it));
		}

		it++;
	}

	int toDeleteEntitiesSize = toDeleteEnemies.size();
	if(toDeleteEntitiesSize > 0)
	{
		if (toDeleteEntitiesSize == 1) DestroyEntity(toDeleteEnemies[0], entitiesPtr);
		else DestroyEntities(&toDeleteEnemies, entitiesPtr);
	}
}
#pragma endregion

//std::ostream& operator<<(std::ostream& os, const Entity entity)
//{
//	os << "Entity = { pos: " /*<< entity.position << "; dir: " << entity.direction */ << "; primaryColor: " << entity.primaryColor << "currentRadius: " << const_cast<Entity&>(entity).GetRadius() << " }";
//	return os;
//}
