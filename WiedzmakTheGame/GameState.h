#pragma once
#include "Graphics/window.h"
#include "GameStateManager.h"
#include "Graphics/renderer.h"

class GameStateManager;
/**
* @brief Class game state interface
*/
class GameState
{
public:
	virtual void update(GameStateManager& gameStateManager, float dt) = 0;
	virtual void render(Renderer& renderer) = 0;
	virtual void handleInput(const Window& window) = 0;
	virtual ~GameState() = default;
};

