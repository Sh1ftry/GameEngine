#pragma once
#include "Graphics/window.h"
#include "GameStateManager.h"
#include "Graphics/renderer.h"
#include <irrKlang/irrKlang.h>

class WiedzmakGame
{
private:
	unsigned int _width = 800;
	unsigned int _height = 600;
	
	Window _window;
	Renderer _renderer;
	GameStateManager _gameStateManager;
	irrklang::ISoundEngine *_soundEngine;
	
	float _dt;
	bool _running;

	void update();
	void render();
	void handleInput();
public:
	WiedzmakGame();
	void run();
};
