#pragma once
#include "GameState.h"
#include <stack>

class GameStateManager
{
private:
	std::stack<GameState*> _gameStates;
public:
	void pushState();
	void popState();
	GameStateManager();
	~GameStateManager();
};

