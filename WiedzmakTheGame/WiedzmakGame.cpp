#include "WiedzmakGame.h"
#include "Utilities/timer.h"
#include "Utilities/resource_manager.h"
#include <glm/gtc/matrix_transform.hpp>
#include "MapState.h"
#include <string>
#include "MenuState.h"
#include "JSONParser.h"

//#define TIME_STOP 

void WiedzmakGame::update()
{
	_gameStateManager.update(_dt);
}

void WiedzmakGame::render()
{
	_gameStateManager.render(*_renderer);
}

void WiedzmakGame::handleInput()
{
	_gameStateManager.handleInput(_window);
}

WiedzmakGame::WiedzmakGame() : _soundEngine(irrklang::createIrrKlangDevice()), _dt(0.0f), _running(true)
{	
	/*
	JSONParser parser("Resources/file_names.json");
	parser.read_info_file();
	_map_manager = parser.parse_JSON_to_map_manager();
	*/

	_window.init("Window", _width, _height);
	_renderer = new Renderer();
	ResourceManager::loadShaders("Resources/text.vert", "Resources/text.frag", "text");
	ResourceManager::loadShaders("Resources/basic.vert", "Resources/basic.frag", "basic");
	ResourceManager::loadFont("Resources/ARCADECLASSIC.TTF", "Arcade20", 20);
	ResourceManager::loadFont("Resources/ARCADECLASSIC.TTF", "Arcade60", 60);
	ResourceManager::loadFont("Resources/ARCADECLASSIC.TTF", "Arcade72", 72);

	ResourceManager::loadFont("Resources/Lato_Regular.ttf", "Lato24", 24);
	ResourceManager::loadFont("Resources/Lato_Regular.ttf", "Lato18", 18);
	

	const glm::mat4 projection = glm::ortho(0.f, 800.f, 0.f, 640.f, -1.0f, 1.0f);
	_renderer->setProjection(projection);

	ResourceManager::loadTexture("Resources/wojteks_house/wojteks_house_0.png", "house_0", 1, 1);
	ResourceManager::loadTexture("Resources/wojteks_house/wojteks_house_1.png", "house_1", 1, 1);
	ResourceManager::loadTexture("Resources/wojteks_house/wojteks_house_2.png", "house_2", 1, 1);

	ResourceManager::loadTexture("Resources/mountain_landscape.png", "mountain", 8, 16);

	ResourceManager::loadTexture("Resources/ranger_m.png", "animations", 4, 3);

	ResourceManager::loadTexture("Resources/battle/battle_stage.png", "arena", 1, 1);

	ResourceManager::loadTexture("Resources/outside/outside_0.png", "outside_0", 1, 1);
	ResourceManager::loadTexture("Resources/outside/outside_1.png", "outside_1", 1, 1);

	ResourceManager::loadTexture("Resources/forest/forest_0.png", "forest_0", 1, 1);
	ResourceManager::loadTexture("Resources/forest/forest_1.png", "forest_1", 1, 1);

	ResourceManager::loadTexture("Resources/prelude/prelude_0.png", "prelude_0", 1, 1);
	ResourceManager::loadTexture("Resources/prelude/prelude_1.png", "prelude_1", 1, 1);

	ResourceManager::loadTexture("Resources/dialog_background.png", "dialogue", 1, 1);

	ResourceManager::loadTexture("Resources/interior.png", "interior", 16, 16);
	ResourceManager::loadTexture("Resources/PathAndObjects.png", "PathAndObjects", 16, 16);
	ResourceManager::loadTexture("Resources/hyptosis_tile-art-batch-1.png", "hyptosis_tile-art-batch-1", 30, 30);
	ResourceManager::loadTexture("Resources/wojteks_house.png", "house", 1, 1);
	ResourceManager::loadTexture("Resources/plx-1.png", "bg1", 1, 1);
	ResourceManager::loadTexture("Resources/plx-4.png", "bg2", 1, 1);
	ResourceManager::loadTexture("Resources/jungle_tileset.png", "jungle_tileset", 19, 39);
	_gameStateManager.pushState(new MenuState(_soundEngine));
}

WiedzmakGame::~WiedzmakGame()
{
	delete _renderer;
	_soundEngine->drop();
}

void WiedzmakGame::run()
{
	const double SEC_PER_UPDATE = 1.0 / 200.0;
	Timer timer;
	double previous = timer.time().count();
	unsigned int fps = 0;
	unsigned int lastFps = 0;
	bool showFps = false;
	unsigned int seconds = 0;

	Timer fpsTimer;
	while (!_window.isClosed())
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		const double current = timer.time().count();
		const double elapsed = current - previous;
		previous = current;
		_dt += elapsed;

		handleInput();
		//while (_dt >= SEC_PER_UPDATE)
		//{
			update();
			_dt = elapsed;
		//	_dt -= SEC_PER_UPDATE;
		//}

		if(fpsTimer.time().count() > 1.0)
		{
#ifdef TIME_STOP
			seconds++;
			if(seconds == 5)
			{
				_running = false;
			}
#endif
			lastFps = fps;
			fps = 0;
			fpsTimer.restart();
			showFps = true;
		}

		fps++;
		render();
		_renderer->useShader(ResourceManager::getShader("text"));
		if (showFps)
		{
			_renderer->drawText(std::to_string(lastFps), ResourceManager::getFont("Arcade20"), glm::vec3(20, 610, 0.9f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		}

		_window.update();
	}
}
