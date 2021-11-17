#include <SFML/Graphics.hpp>
#include "windows.h"
#include "Arthur.h"
#include <iostream>

GameState gameState = GameState::MENU;

void setGameState(GameState actualState)
{
	gameState = actualState;
}

GameState getState()
{
	return gameState;
}