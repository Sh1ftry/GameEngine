#pragma once
#include "GameState.h"
#include "character.h"
#include <string>
#include <vector>
#include "tile.h"

/**
* @brief game state which displays main menu screen
*/

class MenuState : public GameState
{
private:
	std::vector<std::string> _labels;
	std::vector<glm::vec2> _labelsPositions;
	int _activeLabel;
	bool _keyPressed;
	Tile* _background;
	Tile* _tile1;
	Tile* _tile2;
	bool _transition_to_test;
	bool _transition_to_battle;
	bool _quit;
	irrklang::ISoundEngine* _soundEngine;
public:
	MenuState(irrklang::ISoundEngine* soundEngine);
	void update(GameStateManager& gameStateManager, float dt) override;
	void render(Renderer& renderer) override;
	void handleInput(const Window& window) override;
	bool quit() const;
	~MenuState() override;
};
