#pragma once
#include "GameState.h"
#include <string>
#include <vector>
#include "tile.h"

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
public:
	MenuState();
	void update(GameStateManager& gameStateManager, float dt) override;
	void render(Renderer& renderer) override;
	void handleInput(const Window& window) override;
	~MenuState() override;
};
