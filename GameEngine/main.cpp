#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

#include "window.h"
#include "file_reader.h"
#include "shader.h"
#include "renderer2d.h"
#include "timer.h"

int main()
{
	//game window
	Window window("Window", 800, 600);
	glClearColor(0.7f, 0.1f, 0.1f, 1.0f);

	Shader shader("basic.vert", "basic.frag");
	shader.enable();

	const glm::mat4 ortho = glm::ortho(0.f, 800.f, 0.f, 600.f, -1.0f, 1.0f);
	shader.setUniformMat4("projection", ortho);
	//glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "projection"), 1, GL_FALSE, glm::value_ptr(ortho));

	Renderer2D renderer;

	Timer timer;
	unsigned int fps = 0;
	bool up = true;
	//game loop
	while (!window.isClosed())
	{
		const Renderable2D sprite(glm::vec3(300, 300, 0), glm::vec2(200, 200),
		                          glm::vec4((up ? timer.time().count() : 1 - timer.time().count()), 0.388f, (!up ? timer.time().count() : 1 - timer.time().count()), 1.f));
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		renderer.begin();
		renderer.submit(sprite);
		renderer.end();
		renderer.flush();
		//update window state
		window.update();
		fps++;
		if(timer.time().count() > 1.f)
		{
			//one second passed, show fps
			std::cout << fps << std::endl;
			fps = 0;
			timer.restart();
			if (up) up = false;
			else up = true;
		}
	}

	return 0;
}
