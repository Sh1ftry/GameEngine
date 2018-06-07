#include "WiedzmakGame.h"
#include "Utilities/timer.h"
#include "Utilities/resource_manager.h"
#include <glm/gtc/matrix_transform.hpp>
#include "TestState.h"
#include <string>
#include "MenuState.h"

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
	_window.init("Window", _width, _height);
	_renderer = new Renderer();
	ResourceManager::loadShaders("Resources/text.vert", "Resources/text.frag", "text");
	ResourceManager::loadShaders("Resources/basic.vert", "Resources/basic.frag", "basic");
	ResourceManager::loadFont("Resources/ARCADECLASSIC.TTF", "Arcade20", 20);
	ResourceManager::loadFont("Resources/ARCADECLASSIC.TTF", "Arcade72", 72);

	const glm::mat4 projection = glm::ortho(0.f, 800.f, 0.f, 600.f, -1.0f, 1.0f);
	_renderer->setProjection(projection);

	ResourceManager::loadTexture("Resources/plx-1.png", "bg1", 1, 1);
	ResourceManager::loadTexture("Resources/plx-4.png", "bg2", 1, 1);
	ResourceManager::loadTexture("Resources/jungle_tileset.png", "jungle_tileset", 19, 39);
	_gameStateManager.pushState(new MenuState());
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
			_renderer->drawText(std::to_string(lastFps), ResourceManager::getFont("Arcade20"), glm::vec3(20, 570, 0.9f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		}

		_window.update();
	}
}
