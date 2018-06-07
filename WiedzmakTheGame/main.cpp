#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

#include "Graphics/window.h"
#include "Utilities/timer.h"
#include "Graphics/renderer.h"
#include "Utilities/resource_manager.h"
#include "character.h"
#include <vector>
#include "tile.h"
#include <sstream>
#include <irrKlang/irrKlang.h>
#include <iostream>
#include "WiedzmakGame.h"

#include <vld.h>

int main()
{
	std::cout << sizeof(Font) << std::endl;
	std::cout << sizeof(Texture) << std::endl;

	WiedzmakGame wiedzmak;
	try
	{
		wiedzmak.run();
	} catch(const std::exception& e)
	{
		std::cout << e.what();
	}
	//game window
	//Window window("Window", 800, 600);

	//try
	//{
	//	ResourceManager::loadShaders("Resources/text.vert", "Resources/text.frag", "text");
	//	ResourceManager::loadShaders("Resources/basic.vert", "Resources/basic.frag", "basic");

	//	ResourceManager::loadTexture("Resources/jungle_tileset.png", "jungle_tileset", 19, 39);
	//	ResourceManager::loadTexture("Resources/plx-1.png", "bg1", 1, 1);
	//	ResourceManager::loadTexture("Resources/plx-4.png", "bg2", 1, 1);
	//	ResourceManager::loadFont("Resources/ARCADECLASSIC.TTF", "Arcade20", 20);
	//}
	//catch(const std::exception& e)
	//{
	//	std::cout << e.what();
	//	std::cin.ignore();
	//	std::cin.get();
	//	return -1;
	//}

	//Character character = Character(100, 80, 100, 157, SoundEngine);
	//std::vector<Tile*> tiles;

	//Tile* bg1 = new Tile(glm::vec3(0, 0, -0.9f), glm::vec2(800, 600), ResourceManager::getTexture("bg1"));
	//Tile* bg2 = new Tile(glm::vec3(0, 0, -0.9f), glm::vec2(800, 600), ResourceManager::getTexture("bg2"));
	//tiles.push_back(bg1);
	//tiles.push_back(bg2);

	//for(int i = 0; i < 16; i++)
	//{
	//	Tile* newTile = new Tile(glm::vec3(i * 50, 0, -0.9f), glm::vec2(50, 50), ResourceManager::getTexture("jungle_tileset"), glm::vec2(1, 16));
	//	Tile* newTile2= new Tile(glm::vec3(i * 50, 50, -0.9f), glm::vec2(50, 50), ResourceManager::getTexture("jungle_tileset"), glm::vec2(1, 17));
	//	tiles.push_back(newTile);
	//	tiles.push_back(newTile2);
	//}

	//Renderer renderer;
	//Shader* shader = ResourceManager::getShader("basic");
	//Shader* textShader = ResourceManager::getShader("text");
	//const glm::mat4 projection = glm::ortho(0.f, 800.f, 0.f, 600.f, -1.0f, 1.0f);

	//SoundEngine->play2D("Resources/little town - orchestral.ogg", GL_TRUE);

	//Timer timer;
	//Timer frameTimer;
	//unsigned int fps = 0;
	//bool up = true;
	////game loop

	//unsigned int fps_to_show = 0;


	//while (!window.isClosed())
	//{
	//	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//	glClear(GL_COLOR_BUFFER_BIT);

	//	double ftime = frameTimer.time().count();
	//	frameTimer.restart();

	//	std::stringstream sfps;
	//	sfps << fps_to_show;

	//	renderer.useShader(shader);
	//	renderer.setProjection(projection);
	//	
	//	for (Tile* tile : tiles)
	//	{
	//		tile->draw(renderer);
	//	}

	//	character.handleInput(window);
	//	character.update(ftime);
	//	character.draw(renderer);
	//	
	//	renderer.useShader(textShader);
	//	renderer.setProjection(projection);
	//	renderer.drawText(sfps.str(), ResourceManager::getFont("Arcade20"), glm::vec3(20, 570, 0.9f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	//	//update window state
	//	window.update();
	//	fps++;
	//	if (timer.time().count() > 1.0)
	//	{
	//		//one second passed, show fps
	//		fps_to_show = fps;
	//		fps = 0;
	//		timer.restart();
	//		up = !up;
	//	}
	//}

	ResourceManager::clearResources();
	return 0;
}
