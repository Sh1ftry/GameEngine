#pragma once
#include "GameState.h"
#include <stack>

class GameStateManager
{
private:
	std::stack<GameState*> _gameStates;
public:
	void pushState(GameState* gameState);
	void popState();

	void render();
	void handleInput();
	void update(float dt);

	GameStateManager() = default;
	~GameStateManager();
};

