#pragma once
#include "GameState.h"
#include <irrKlang/ik_ISoundEngine.h>
#include "tile.h"
#include <vector>

/**
* @brief game state which displays game over screen
*/

class ExitState :
	public GameState
{
private:
	std::string label;
	Tile* _background;
	irrklang::ISoundEngine* _soundEngine;
public:
	ExitState(irrklang::ISoundEngine* soundEngine);
	~ExitState();
	void update(GameStateManager& gameStateManager, float dt) override;
	void render(Renderer& renderer) override;
	void handleInput(const Window& window) override;
};

