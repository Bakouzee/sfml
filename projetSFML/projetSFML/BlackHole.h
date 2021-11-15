#pragma once
#define PI 3.1415926535f
#include <list>

#include "Entities.h"

struct ColorsParameters
{
public:
	enum ColorType
	{
		Primary,
		Secondary,
		Mixed
	};

	ColorType colorType;
	int step;

	ColorsParameters(ColorType colorType, int step = 1);
	ColorsParameters();
};

struct AttackPattern
{
private:
	int waveCount;
	float radWaveOffset;
	float waveDuration;

	int projectileNumber;
	float projectileSpeed;
	MinMax projectileMinMaxRadius;

	int currentWave;

public:
	float GetAttackDuration();

	void SpawnWave(int waveIndex, Vector2 spawnPos, std::list<Entity>* entitiesPtr);

	float waveTimer;
	bool IsFinished();
	void SpawnWaveIfFinished(Vector2 spawnPos, std::list<Entity>* entitiesPtr);

	AttackPattern(int waveCount, float radWaveOffset, float waveDuration, int projectileNumber, float projectileSpeed, MinMax projRadiusMinMax, ColorsParameters colorsParam);

	ColorsParameters colorsParam;

	void Reset()
	{
		waveTimer = waveDuration;
	}
};

struct BlackHole
{
public:
	Vector2* position;

	float attackTimer;

	AttackPattern* currentAttackPtr;

	BlackHole(Vector2 pos, float timeBetweenAttacks);

	void LaunchNewAttack(std::list<Entity>* entitiesPtr);

private:
	float timeBetweenAttacks;
};

const ColorsParameters primaryColorParam(ColorsParameters::ColorType::Primary);
const ColorsParameters secondaryColorParam(ColorsParameters::ColorType::Secondary);
const ColorsParameters mixedColorParam(ColorsParameters::ColorType::Mixed, 1);

const MinMax stdRadius(10, 30);
const MinMax littleRadius(10, 15);

AttackPattern* GetRandomAttack();