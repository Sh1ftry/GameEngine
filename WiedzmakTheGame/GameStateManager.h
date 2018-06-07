#pragma once
#include "GameState.h"
#include "Graphics/renderer.h"
#include <stack>

class GameState;

class GameStateManager
{
private:
	std::stack<GameState*> _gameStates;
public:
	void pushState(GameState* gameState);
	void popState();

	void render(Renderer& renderer);
	void handleInput(const Window& window);
	void update(float dt);

	GameStateManager() = default;
	~GameStateManager();
};

