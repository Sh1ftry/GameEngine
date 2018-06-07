#include "MenuState.h"
#include "Utilities/resource_manager.h"

MenuState::MenuState()
{
	const Font* font = ResourceManager::getFont("Arcade72");
	_labels.push_back("New Game");
	_labels.push_back("Load Game");
	_labels.push_back("Options");
	_labels.push_back("Credits");
	_labels.push_back("Quit");

	unsigned int y = 450;
	for(std::string label : _labels)
	{
		glm::vec2 pos = font->getTextSize(label);
		y -= (pos.y + 10);
		unsigned int x = 400 - pos.x / 2;
		_labelsPositions.emplace_back(glm::vec2(x, y));
	}

	_background = new Tile(glm::vec3(0, 0, -0.9f), glm::vec2(800, 600), ResourceManager::getTexture("bg1"));
	_tile1 = new Tile(glm::vec3(0, 0, -0.9f), glm::vec2(800, 600), ResourceManager::getTexture("bg2"));
	_tile2 = new Tile(glm::vec3(-800, 0, -0.9f), glm::vec2(800, 600), ResourceManager::getTexture("bg2"));

	_activeLabel = 0;
}

void MenuState::update(GameStateManager & gameStateManager, float dt)
{
	glm::vec3 pos1 = _tile1->getPosition();
	pos1.x += 50 * dt;
	glm::vec3 pos2 = _tile2->getPosition();
	pos2.x += 50 * dt;
	
	if(pos1.x > pos2.x)
	{
		//tile1 jest na prawo od tile2
		if(pos1.x >= 800)
		{
			pos1.x = pos2.x - 800;
		}
	}
	else
	{
		//tile1 jest na lewo od tile2
		if(pos2.x >= 800)
		{
			pos2.x = pos1.x - 800;
		}
	}
	
	_tile1->setPosition(pos1);
	_tile2->setPosition(pos2);
}

void MenuState::render(Renderer & renderer)
{
	renderer.useShader(ResourceManager::getShader("basic"));
	_background->draw(renderer);
	_tile1->draw(renderer);
	_tile2->draw(renderer);

	const Font* font = ResourceManager::getFont("Arcade72");
	renderer.useShader(ResourceManager::getShader("text"));
	for (int i = 0; i < _labels.size(); i++)
	{
		renderer.drawText(_labels[i], font, glm::vec3(_labelsPositions[i].x + 3, _labelsPositions[i].y - 3, 0), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		if (i != _activeLabel) renderer.drawText(_labels[i], font, glm::vec3(_labelsPositions[i], 0), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		else renderer.drawText(_labels[i], font, glm::vec3(_labelsPositions[i], 0), glm::vec4(0.6f, 0.4f, 0.2f, 1.0f));
	}
}

void MenuState::handleInput(const Window & window)
{
	if (!window.isKeyboardKeyPressed(GLFW_KEY_UP) && !window.isKeyboardKeyPressed(GLFW_KEY_DOWN)) _keyPressed = false;
	if(window.isKeyboardKeyPressed(GLFW_KEY_UP) && !_keyPressed)
	{
		_keyPressed = true;
		_activeLabel--;
		if (_activeLabel < 0) _activeLabel = 0;
	}
	else if (window.isKeyboardKeyPressed(GLFW_KEY_DOWN) && !_keyPressed)
	{
		_keyPressed = true;
		_activeLabel++;
		if (_activeLabel > 4) _activeLabel = 4;
	}
}

MenuState::~MenuState()
{
	delete _background;
	delete _tile1;
	delete _tile2;
}
