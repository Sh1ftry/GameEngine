#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

#include "window.h"
#include "file_reader.h"
#include "shader.h"
#include "renderable2d.h"
#include "simple_renderer2d.h"

int main()
{
	//game window
	Window window("Window", 800, 600);
	glClearColor(0.7f, 0.1f, 0.1f, 1.0f);

	Shader shader("basic.vert", "basic.frag");
	shader.enable();

	glm::mat4 ortho = glm::ortho(0.f, 800.f, 0.f, 600.f, -1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "projection"), 1, GL_FALSE, glm::value_ptr(ortho));

	const Renderable2D sprite(glm::vec3(300, 300, 0), glm::vec2(200, 200), glm::vec4(1.000, 0.388, 0.278, 1), shader);
	SimpleRenderer2D renderer;

	//game loop
	while (!window.isClosed())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		renderer.submit(sprite);
		renderer.flush();
		//update window state
		window.update();
	}

	return 0;
}
