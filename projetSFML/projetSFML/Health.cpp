#include "Arthur.h"

sf::ConvexShape lifeCircle()
{
	sf::ConvexShape heart;
	heart.setPointCount(242);
	int o = 0;
	for (float t = 0; t <= 60; t += 0.5f)
	{
		float x = -0.01f * (-pow(t, 2) + 40 * t + 1200) * sin(PI * t / 180);
		float y = 0.01f * (-pow(t, 2) + 40 * t + 1200) * cos(PI * t / 180);

		heart.setPoint(o, sf::Vector2f(x * 3, -y * 3));
		o++;
	}
	for (float t = 60; t >= 0; t -= 0.5f)
	{
		float x = 0.01f * (-pow(t, 2) + 40 * t + 1200) * sin(PI * t / 180);
		float y = 0.01f * (-pow(t, 2) + 40 * t + 1200) * cos(PI * t / 180);

		heart.setPoint(o, sf::Vector2f(x * 3, -y * 3));
		o++;
	}

	float circleLifeRadius = 20;
	heart.setFillColor(sf::Color::Red);
	heart.setOutlineThickness(2);
	heart.setOutlineColor(sf::Color::White);
	return heart;
}

void SetPositionLifeCircle(Player& actualPlayer, float circleLifeRadius, float screenResolutionX)
{
	float posX = 0;
	float offSet = 0;
	float multiplicateur = 0;

	if(actualPlayer.numberPlayer == 1)
	{
		posX = 80;
		offSet = 20;
		multiplicateur = 1;
	}
	else
	{
		posX = screenResolutionX - 80;
		offSet = -20;
		multiplicateur = -1;
	}

	for(int i = 0; i < 3; i++)
	{
		actualPlayer.tabLifeCircle[i].setPosition(posX, 120);
		posX += multiplicateur * circleLifeRadius * 2 + offSet;
	}
}

void Player::AdjustLife(int lifeChange, sf::Clock* playerScoreClock)
{
	if (lifeChange == 1 && actualLife != 3)
	{
		tabLifeCircle[actualLife].setFillColor(sf::Color(180, 0, 0, 255));
		actualLife += lifeChange;
	}
	else if (lifeChange == -1 && actualLife != 0)
	{
		tabLifeCircle[actualLife - 1].setFillColor(sf::Color(0, 0, 0, 0));
		actualLife += lifeChange;
		playerScoreClock->restart();
		PlayHurtSound();
	}

	if (actualLife <= 0) isDead = true;
}
void Player::SetColors(const Colors& colors)
{
	player.setFillColor(colors.primary);
	player.setOutlineColor(colors.secondary);
}
void Player::OnCollisionWithEntities(std::list<Entity>* allEntities, std::vector<Entity*> entitiesColliding,
	const Colors& playerColor, const Colors& entitiesColors, 
	float& combo, sf::Clock& comboTimer, sf::Clock* playerScoreClock, Player& playerColliding)
{
	bool takeDamage = false;

	if (playerColliding.takeDamage == false) {
		for (Entity* entite : entitiesColliding)
		{
			sf::Color entityColor = entite->primaryColor ? entitiesColors.primary : entitiesColors.secondary;
			if (entityColor != playerColor.primary)
			{
				takeDamage = true;
				playerColliding.takeDamage = true;
				combo = 0.f;
			}
			else {
				combo += 0.3f;
				comboTimer.restart();
				if (comboTimer.getElapsedTime().asSeconds() >= 1.5f) {
					combo = 0.f;
				}
			}
			DestroyEntity(entite, allEntities);
		}
		if (takeDamage) {
			AdjustLife(-1, playerScoreClock);
		}
	}
	
}