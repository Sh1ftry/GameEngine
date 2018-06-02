#include "WiedzmakGame.h"
#include "Utilities/timer.h"

void WiedzmakGame::update()
{
	_gameStateManager.update(_dt);
}

void WiedzmakGame::render()
{
	_gameStateManager.render();
}

void WiedzmakGame::handleInput()
{
	_gameStateManager.handleInput();
}

WiedzmakGame::WiedzmakGame() : _soundEngine(irrklang::createIrrKlangDevice()), _dt(0.0f), _running(true)
{
	_window.init("Window", _width, _height);
}

void WiedzmakGame::run()
{
	const float SEC_PER_UPDATE = 1.0f;
	Timer timer;
	double previous = timer.time();
	while (_running)
	{
		const double current = timer.time();
		const double elapsed = current - previous;
		previous = current;
		_dt += elapsed;

		handleInput();

		while (_dt >= SEC_PER_UPDATE)
		{
			update();
			_dt -= SEC_PER_UPDATE;
		}

		render();
	}
}
