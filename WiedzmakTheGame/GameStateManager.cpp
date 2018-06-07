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

void GameStateManager::render(Renderer& renderer)
{
	_gameStates.top()->render(renderer);
}

void GameStateManager::handleInput(const Window& window)
{
	_gameStates.top()->handleInput(window);
}

void GameStateManager::update(float dt)
{
	_gameStates.top()->update(*this, dt);
}


GameStateManager::~GameStateManager()
{
	while(!_gameStates.empty())
	{
		popState();
	}
}
