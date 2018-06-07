#include "TestState.h"



TestState::TestState(irrklang::ISoundEngine* soundEngine) : _soundEngine(soundEngine)
{
	_character = new Character(100, 80, 100, 157, _soundEngine);

	Tile* bg1 = new Tile(glm::vec3(0, 0, -0.9f), glm::vec2(800, 600), ResourceManager::getTexture("bg1"));
	Tile* bg2 = new Tile(glm::vec3(0, 0, -0.9f), glm::vec2(800, 600), ResourceManager::getTexture("bg2"));
	_tiles.push_back(bg1);
	_tiles.push_back(bg2);

	for (int i = 0; i < 16; i++)
	{
		Tile* newTile = new Tile(glm::vec3(i * 50, 0, -0.9f), glm::vec2(50, 50), ResourceManager::getTexture("jungle_tileset"), glm::vec2(1, 16));
		Tile* newTile2 = new Tile(glm::vec3(i * 50, 50, -0.9f), glm::vec2(50, 50), ResourceManager::getTexture("jungle_tileset"), glm::vec2(1, 17));
		_tiles.push_back(newTile);
		_tiles.push_back(newTile2);
	}
}


TestState::~TestState()
{
	delete _character;
	for(Tile* tile : _tiles)
	{
		delete tile;
	}
}

void TestState::update(GameStateManager& gameStateManager, float dt)
{
	_character->update(dt);
}

void TestState::render(Renderer& renderer)
{
	renderer.useShader(ResourceManager::getShader("basic"));
	for (Tile* tile : _tiles)
	{
		tile->draw(renderer);
	}
	_character->draw(renderer);
}

void TestState::handleInput(const Window& window)
{
	_character->handleInput(window);
}
