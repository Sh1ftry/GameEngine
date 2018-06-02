#include "GameStateManager.h"

void GameStateManager::pushState(GameState* gameState)
{
	_gameStates.push(gameState);
}

void GameStateManager::popState()
{
	if (_gameStates.empty()) return;
	GameState* gameState = _gameStates.top();
	_gameStates.pop();
	delete gameState;
}

void GameStateManager::render()
{
}

void GameStateManager::handleInput()
{
}

void GameStateManager::update(float dt)
{
}


GameStateManager::~GameStateManager()
{
	while(!_gameStates.empty())
	{
		popState();
	}
}
