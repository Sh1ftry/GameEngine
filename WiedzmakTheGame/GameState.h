#pragma once
#include "Graphics/window.h"
#include "GameStateManager.h"
#include "Graphics/renderer.h"

class GameStateManager;

class GameState
{
public:
	void update(GameStateManager* gameStateManager);
	void draw(Renderer* renderer);
	void handleInput(const Window* window);
	virtual ~GameState() = default;
};

