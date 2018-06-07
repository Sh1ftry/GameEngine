#pragma once
#include "GameState.h"
#include "character.h"
#include "tile.h"

class TestState : public GameState
{
private:
	Character* _character;
	std::vector<Tile*> _tiles;
	irrklang::ISoundEngine* _soundEngine;
public:
	TestState(irrklang::ISoundEngine* soundEngine);
	~TestState();
	void update(GameStateManager& gameStateManager, float dt) override;
	void render(Renderer& renderer) override;
	void handleInput(const Window& window) override;
};

