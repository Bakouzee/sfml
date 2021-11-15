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
	float waveAngleOffset = waveIndex * radWaveOffset + globalRadOffset;

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
		else if (colorsParam.colorType == ColorsParameters::ColorType::Mixed)
		{
			primaryColor = i % (colorsParam.step * 2) < colorsParam.step;
		}

		// Add it to entities list
		entitiesPtr->push_back(Entity(spawnPos, dir, projectileSpeed, primaryColor, projectileMinMaxRadius));
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
	if (IsFinished())
	{
		SpawnWave(currentWave, spawnPos, entitiesPtr);
	}
}

AttackPattern::AttackPattern(int waveCount, float globalRadOffset, float radWaveOffset, float waveDuration, int projectileNumber,
	float projectileSpeed, MinMax projRadiusMinMax, ColorsParameters colorsParam)
{
	this->waveCount = waveCount;
	this->globalRadOffset = globalRadOffset;
	this->radWaveOffset = radWaveOffset;
	this->waveDuration = waveDuration;
	this->projectileNumber = projectileNumber;
	this->projectileMinMaxRadius = projRadiusMinMax;
	this->projectileSpeed = projectileSpeed;
	this->colorsParam = colorsParam;

	currentWave = 0;
	waveTimer = waveDuration;
}


void BlackHole::ChooseRandomAttack()
{
	currentAttackPtr = &possibleAttacks->at(rand() % numberOfAttack);
}

BlackHole::BlackHole(Vector2 pos, float timeBetweenAttacks, std::vector<AttackPattern>* possibleAttacks)
{
	this->position = new Vector2(pos.x, pos.y);

	attackTimer = 0;
	this->timeBetweenAttacks = timeBetweenAttacks;

	// Attacks
	this->numberOfAttack = possibleAttacks->size();
	this->possibleAttacks = possibleAttacks;
	ChooseRandomAttack();
}

void BlackHole::LaunchNewAttack(std::list<Entity>* entitiesPtr)
{
	// Choose new attack and reset it
	ChooseRandomAttack();

	// Set attack timer
	attackTimer = currentAttackPtr->GetAttackDuration() + timeBetweenAttacks;

	currentAttackPtr->Reset();

	// Spawn first wave
	currentAttackPtr->SpawnWave(0, *position, entitiesPtr);
}

#pragma region All Attacks pattern definition

// Colors parameters
ColorsParameters primaryColorParam(ColorsParameters::ColorType::Primary);
ColorsParameters secondaryColorParam(ColorsParameters::ColorType::Secondary);
ColorsParameters mixedColorParam(ColorsParameters::ColorType::Mixed, 1);

// Radius
MinMax stdRadius(10, 30);
MinMax littleRadius(10, 15);

// All Attacks
/// AttackPattern( nombre de waves, rotation par wave en radians, durée d'une wave,
/// nombre de projectile dans une wave, vitesse des projectiles, MinMax du radius des proj,
/// Paramètres de couleurs (primary/secondary/mixed) )
AttackPattern allAttacks[] = {
	// Star pattern
	AttackPattern(
		5, // Wave count
		0, // Start rotation
		0, // Rotation per wave
		0.05f, // Wave duration (time before next wave)
		8, // Number of proj in a wave
		1.5f, // Proj speed
		stdRadius, // Min Max proj radius
		primaryColorParam // Proj colors parameters
	),

	// Star pattern
	AttackPattern(
		5,
		0,
		PI / 4, 
		0.2f, 
		4, 
		1.0f, 
		stdRadius, 
		primaryColorParam 
	)

	//AttackPattern(4, 0, 0.2f, 5, 1.25f, stdRadius, primaryColorParam),
	//AttackPattern(4, -1, 0.2f, 5, 1.25f, stdRadius, secondaryColorParam),
	//AttackPattern(4, PI / 4, 0.2f, 5, 0.9f, littleRadius, mixedColorParam),
	//AttackPattern(8, 0, 0.2f, 10, 0.9f, littleRadius, primaryColorParam),
	//AttackPattern(6, PI / 16, 0.35f, 8, 0.9f, littleRadius, mixedColorParam),
	//AttackPattern(6, PI / 16, 0.35f, 8, 0.9f, littleRadius, mixedColorParam),
};
#pragma endregion
void GetRandomAttack()
{
	 
}
