#include "ExitState.h"
#include "Utilities/resource_manager.h"


ExitState::ExitState(irrklang::ISoundEngine* soundEngine) : _soundEngine(soundEngine)
{
	label = "GAME OVER";
	ResourceManager::loadTexture("Resources/end_card.png", "end", 1, 1);
	_background = new Tile(glm::vec3(0, 0, 0), glm::vec2(800, 640), ResourceManager::getTexture("end"));
	
	_soundEngine->stopAllSounds();
	_soundEngine->play2D("Resources/music/BoxCat_Games_-_26_-_Defeat.mp3", GL_TRUE);
}

void ExitState::update(GameStateManager& gameStateManager, float dt)
{
}

void ExitState::render(Renderer& renderer)
{
	renderer.useShader(ResourceManager::getShader("basic"));
	_background->draw(renderer);
	const Font* font = ResourceManager::getFont("Arcade72");
	renderer.useShader(ResourceManager::getShader("text"));
	renderer.drawText(label, font, glm::vec3(273, 317, 0), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	renderer.drawText(label, font, glm::vec3(270, 320, 0), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
}

void ExitState::handleInput(const Window& window)
{
}

ExitState::~ExitState()
{
}
