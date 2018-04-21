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
#include <vector>

int main()
{
	//game window
	Window window("Window", 800, 600);
	glClearColor(0.7f, 0.1f, 0.1f, 1.0f);

	Shader shader("basic.vert", "basic.frag");
	shader.enable();

	const glm::mat4 ortho = glm::ortho(0.f, 800.f, 0.f, 600.f, -1.0f, 1.0f);
	shader.setUniformMat4("projection", ortho);

	std::vector<Renderable2D> sprites;
	for(int i = 0; i < 100; i+=1)
	{
		for(int j = 0; j < 100; j+=1)
		{
			sprites.push_back(Renderable2D(glm::vec3((float)i * 8, (float)j * 6, 0), glm::vec2(7.9f, 5.9f), glm::vec4(static_cast<float>(i) / 100, static_cast<float>(j) / 100, 0.5f, 1.f)));
		}
	}
	
	Renderer2D renderer;
	Timer timer;
	unsigned int fps = 0;
	bool up = true;
	//game loop
	while (!window.isClosed())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		double x;
		double y;
		window.getMouseCursorPosition(x, y);
		shader.setUniform2f("light_position", glm::vec2(x,600 - y));
		renderer.begin();
		for(std::vector<Renderable2D>::const_iterator it = sprites.begin(); it != sprites.end(); ++it)
		{
			renderer.submit(*it);
		}
		renderer.end();
		renderer.flush();
		//update window state
		window.update();
		fps++;
		if(timer.time().count() > 1.f)
		{
			//one second passed, show fps
			//std::cout << fps << std::endl;
			fps = 0;
			timer.restart();
			up = !up;
		}
	}

	return 0;
}
