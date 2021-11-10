#include "BlackHole.h"

#include <iostream>

float AttackPattern::GetAttackDuration()
{
	return waveCount * waveDuration;
}

void AttackPattern::SpawnWave(int waveIndex, Vector2 spawnPos, std::list<Entity>* entitiesPtr)
{
	float waveAngleOffset = waveIndex * radWaveOffset;

	// For each projectile of the wave
	for (int i = 0; i < projectileNumber; ++i)
	{
		// Create entity parameters
		float angle = i / float(projectileNumber) * 2.0f * PI + waveAngleOffset;
		Vector2 dir(cos(angle), sin(angle));
		//std::cout << spawnPos << " " << dir << " " << dir.Normalize() << std::endl;

		// Add it to entities list
		entitiesPtr->push_back(Entity(spawnPos, dir, projectileSpeed, rand() % 2 == 0, MinMax(5.0, 15.0)));
	}

	waveCount++;
	waveTimer = waveDuration;
}

bool AttackPattern::IsFinished()
{
	return waveTimer <= 0;
}

void AttackPattern::SpawnWaveIfFinished(Vector2 spawnPos, std::list<Entity>* entitiesPtr)
{
	if(IsFinished())
	{
		SpawnWave(currentWave, spawnPos, entitiesPtr);
	}
}

AttackPattern::AttackPattern(int waveCount, float radWaveOffset, float waveDuration, int projectileNumber,
                           float projectileSpeed)
{
	this->waveCount = waveCount;
	this->radWaveOffset = radWaveOffset;
	this->waveDuration = waveDuration;
	this->projectileNumber = projectileNumber;
	this->projectileSpeed = projectileSpeed;

	currentWave = 0;
	waveTimer = waveDuration;
}

BlackHole::BlackHole(Vector2 pos, float timeBetweenAttacks, std::list<AttackPattern>& attacks)
{
	this->position = new Vector2(pos.x, pos.y);
	possibleAttacks = attacks;

	attackTimer = 0;
	this->timeBetweenAttacks = timeBetweenAttacks;

	currentAttackPtr = &(possibleAttacks.front());
}

void BlackHole::LaunchNewAttack(std::list<Entity>* entitiesPtr)
{
	int newAttackIndex = rand() % possibleAttacks.size();
	auto it = possibleAttacks.begin();
	for (int i = 0; i < possibleAttacks.size(); ++i)
	{
		if(newAttackIndex == i)
		{
			currentAttackPtr = &(*it);
		}
		else it++;
	}

	attackTimer = currentAttackPtr->GetAttackDuration() + timeBetweenAttacks;
	currentAttackPtr->Reset();

	currentAttackPtr->SpawnWave(0, *position, entitiesPtr);
}
