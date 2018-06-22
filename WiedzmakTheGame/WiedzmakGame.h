#pragma once
#include "Graphics/window.h"
#include "GameStateManager.h"
#include "Graphics/renderer.h"
#include <irrKlang/irrKlang.h>
#include "MapManager.h"

/**
* @brief start-up class that loads all files, prepares the game and initialize the first game state
*/

class WiedzmakGame
{
private:
	unsigned int _width = 800;
	unsigned int _height = 640;

	MapManager _map_manager;
	Window _window;
	Renderer* _renderer;
	GameStateManager _gameStateManager;
	irrklang::ISoundEngine* _soundEngine;
	
	double _dt;
	bool _running;

	void update();
	void render();
	void handleInput();
public:
	WiedzmakGame();
	~WiedzmakGame();
	void run();
};
