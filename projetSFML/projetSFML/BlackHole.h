#pragma once
#define PI 3.1415926535
#include <list>

#include "Entities.h"

/// <summary>
/// How to use
/// </summary>
struct AttackPattern
{
private:
	int waveCount;
	float radWaveOffset;
	float waveDuration;

	int projectileNumber;
	float projectileSpeed;

	int currentWave;

public:
	float GetAttackDuration();

	void SpawnWave(int waveIndex, Vector2 spawnPos, std::list<Entity>* entitiesPtr);

	float waveTimer;
	bool IsFinished();
	void SpawnWaveIfFinished(Vector2 spawnPos, std::list<Entity>* entitiesPtr);

	AttackPattern(int waveCount, float radWaveOffset, float waveDuration, int projectileNumber, float projectileSpeed);

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

	BlackHole(Vector2 pos, float timeBetweenAttacks, std::list<AttackPattern>& attacks);

	void LaunchNewAttack(std::list<Entity>* entitiesPtr);

private:
	std::list<AttackPattern> possibleAttacks;

	float timeBetweenAttacks;
};