#include "renderer.h"
#include <glm/gtc/matrix_transform.hpp>

Renderer::Renderer(Shader* shader)
	: _shader(shader)
{
	GLuint vertexBuffer;
	GLuint _elementBuffer;
	GLushort indexes[] = { 0, 1, 2, 2, 3, 0 };
	GLfloat vertices[] = 
	{
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
	};

	glGenBuffers(1, &_elementBuffer);
	glGenBuffers(1, &vertexBuffer);
	
	glGenVertexArrays(1, &_vertexArray);
	glBindVertexArray(_vertexArray);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	//position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), static_cast<GLvoid*>(0));
	//tex coordinates
	//glVertexAttribPointer(1, sizeof(VertexData::color), GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid*)sizeof(VertexData::position));
	
	glEnableVertexAttribArray(0);

	glBindVertexArray(NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);
}

Renderer::~Renderer()
{
	//glDeleteVertexArrays()
}

void Renderer::draw(const Renderable2D& renderable) const
{
	const glm::vec3& position = renderable.getPosition();
	const glm::vec4& color = renderable.getColor();
	const glm::vec2& size = renderable.getSize();

	glm::mat4 model(1.0f);
	model = glm::translate(model, position);
	model = glm::scale(model, glm::vec3(size, 1.0f));

	_shader->enable();
	_shader->setUniformMat4("model", model);
	_shader->setUniform4f("col", color);

	glBindVertexArray(_vertexArray);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, static_cast<GLvoid*>(0));
	glBindVertexArray(NULL);
	_shader->disable();

}
