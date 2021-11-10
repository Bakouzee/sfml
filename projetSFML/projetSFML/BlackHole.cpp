#include "BlackHole.h"
#include <iostream>

ColorsParameters::ColorsParameters(ColorType colorType, int step)
{
	this->colorType = colorType;
	this->step = step;
}

ColorsParameters::ColorsParameters()
{
	this->colorType = ColorType::Primary;
	this->step = 1;
}

float AttackPattern::GetAttackDuration()
{
	return waveCount * waveDuration;
}

void AttackPattern::SpawnWave(int waveIndex, Vector2 spawnPos, std::list<Entity>* entitiesPtr)
{
	std::cout << waveIndex << std::endl;
	float waveAngleOffset = waveIndex * radWaveOffset;

	// For each projectile of the wave
	for (int i = 0; i < projectileNumber; ++i)
	{
		// Create entity parameters
		float angle = i / float(projectileNumber) * 2.0f * PI;
		angle += waveAngleOffset;
		Vector2 dir(cos(angle), sin(angle));
		//std::cout << spawnPos << " " << dir << " " << dir.Normalize() << std::endl;

		// Set color
		bool primaryColor = true;
		if (colorsParam.colorType == ColorsParameters::ColorType::Secondary) primaryColor = false;
		else if(colorsParam.colorType == ColorsParameters::ColorType::Mixed)
		{
			primaryColor = i % (colorsParam.step * 2) < colorsParam.step;
		}

		// Add it to entities list
		entitiesPtr->push_back(Entity(spawnPos, dir, projectileSpeed, primaryColor, MinMax(5.0, 15.0)));
	}

	currentWave++;
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

AttackPattern::AttackPattern(int waveCount, float radWaveOffset, float waveDuration, int projectileNumber, float projectileSpeed, 
	ColorsParameters colorsParam)
{
	this->waveCount = waveCount;
	this->radWaveOffset = radWaveOffset;
	this->waveDuration = waveDuration;
	this->projectileNumber = projectileNumber;
	this->projectileSpeed = projectileSpeed;
	this->colorsParam = colorsParam;

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
