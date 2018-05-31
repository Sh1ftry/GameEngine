#pragma once
#include "Graphics/window.h"
#include "GameStateManager.h"
#include "Graphics/renderer.h"

class WiedzmakGame
{
private:
	Window _window;
	Renderer* _renderer;
	GameStateManager _gameStateManager;
	
	float dt;

	void update();
	void draw();
	void handleInput();
public:
	void run();
};
