#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.inl>
#include <GL/glew.h>

#include "window.h"
#include "file_reader.h"
#include "shader.h"
#include "buffer.h"
#include "vertexarray.h"
#include "indexbuffer.h"

int main()
{
	//game window
	Window window("Window", 800, 600);
	glClearColor(0.7f, 0.1f, 0.1f, 1.0f);

	/*GLfloat vertices[] =
	{
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
		 0.5f,	0.5f, 0.0f,
		 0.5f,	0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glm::mat4 ortho = glm::ortho(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("basic.vert", "basic.frag");
	shader.enable();
	glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "projection"), 1, GL_FALSE, glm::value_ptr(ortho));*/

	GLfloat vertices[] =
	{
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
		0.5f,	0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
	};

	GLushort indices[] =
	{
		0, 1, 2, 2, 3, 0
	};

	Buffer* vbo = new Buffer(vertices, 4 * 3, 3);
	IndexBuffer ibo(indices, 6);

	VertexArray vao;
	vao.addBuffer(vbo, 0);

	Shader shader("basic.vert", "basic.frag");
	shader.enable();

	glm::mat4 ortho = glm::ortho(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "projection"), 1, GL_FALSE, glm::value_ptr(ortho));

	//game loop
	while (!window.isClosed())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		vao.bind();
		ibo.bind();
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
		ibo.unbind();
		vao.unbind();
		//update window state
		window.update();
	}

	return 0;
}