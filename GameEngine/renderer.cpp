#include "renderer.h"
#include <glm/gtc/matrix_transform.hpp>

Renderer::Renderer()
{
	GLuint vertexBuffer;
	unsigned int indexes[] = { 0, 1, 2, 2, 3, 0 };
	float vertices[] = 
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
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	//position
	glVertexAttribPointer(0, sizeof(VertexData::position), GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid*)0);
	//tex coordinates
	//glVertexAttribPointer(1, sizeof(VertexData::color), GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid*)sizeof(VertexData::position));
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, NULL);
	glBindVertexArray(NULL);
}

Renderer::~Renderer()
{
	glDeleteBuffers(1, &_elementBuffer);
}

void Renderer::draw(const Renderable2D* renderable, glm::vec4 color) const
{
	const glm::vec3& position = renderable->getPosition();
	const glm::vec4& color = renderable->getColor();
	const glm::vec2& size = renderable->getSize();

	glm::mat4 modelMatrix;
	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix = glm::scale(modelMatrix, glm::vec3(size, 1.0f));

	_shader->enable();
	_shader->setUniformMat4("model", modelMatrix);
	_shader->setUniform4f("col", color);

	glBindVertexArray(_vertexArray);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(NULL);
	_shader->disable();

}
