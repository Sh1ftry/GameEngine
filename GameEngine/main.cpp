#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

#include "window.h"
#include "file_reader.h"
#include "shader.h"
#include "timer.h"
#include "renderer.h"
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
	
	Renderer renderer(&shader);
	Timer timer;
	unsigned int fps = 0;
	bool up = true;
	//game loop
	while (!window.isClosed())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for(int i = 0; i < 80; i++)
			for(int j = 0; j < 60; j++)
				renderer.draw(Renderable2D(glm::vec3(i*10, j*10, 0), glm::vec2(9.9f, 9.9f), glm::vec4(0.4f, 0.6f, 0.7f, 1.0f)));
		
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
