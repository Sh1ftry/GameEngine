#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

#include "window.h"
#include "shader.h"
#include "timer.h"
#include "renderer.h"
#include "resource_manager.h"
#include "animation.h"
#include "animated_sprite.h"
#include "character.h"

int main()
{
	//game window
	Window window("Window", 800, 600);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	Shader shader("basic.vert", "basic.frag");
	shader.enable();

	const glm::mat4 ortho = glm::ortho(0.f, 800.f, 0.f, 600.f, -1.0f, 1.0f);
	shader.setUniformMat4("projection", ortho);
	
	ResourceManager::loadTexture("sheet_hero_idle.png", "idle", 1, 8);
	ResourceManager::loadTexture("sheet_hero_dead.png", "dead", 1, 8);

	Animation animation = Animation(ResourceManager::getTexture("idle"), glm::vec2(0, 0), glm::vec2(7, 0), 0.8f);
	Character character = Character(100, 100, 500, 500, animation, "idle");

	Renderer renderer(&shader);
	Timer timer;
	Timer frameTimer;
	unsigned int fps = 0;
	bool up = true;
	//game loop

	while (!window.isClosed())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		character.update(frameTimer.time().count());
		frameTimer.restart();
		character.draw(renderer);

		//update window state
		window.update();
		fps++;
		if(timer.time().count() > 1.f)
		{
			//one second passed, show fps
			std::cout << fps << std::endl;
			fps = 0;
			timer.restart();
			up = !up;
		}
	}

	return 0;
}
