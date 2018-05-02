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
		0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), reinterpret_cast<GLvoid*>(offsetof(VertexData, VertexData::position)));
	
	//tex coordinates
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), reinterpret_cast<GLvoid*>(offsetof(VertexData, VertexData::texturePosition)));
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);
}

Renderer::~Renderer()
{
	//glDeleteVertexArrays()
}

void Renderer::draw(const glm::vec3 & position, const glm::vec2 & size, const glm::vec4 & color)
{
	glm::mat4 model(1.0f);
	model = glm::translate(model, position);
	model = glm::scale(model, glm::vec3(size, 1.0f));

	_shader->enable();
	_shader->setUniformMat4("model", model);
	_shader->setUniform4f("col", color);

	glBindVertexArray(_vertexArray);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
	glBindVertexArray(NULL);
	_shader->disable();

}

void Renderer::draw(const glm::vec3 & position, const glm::vec2 & size, const Texture & texture, const glm::vec2 & texturePosition, const glm::vec2 & textureSize)
{

	glm::mat4 model(1.0f);
	model = glm::translate(model, position);
	model = glm::scale(model, glm::vec3(size, 1.0f));

	const glm::vec2 tPos = texturePosition / texture.getSize();
	const glm::vec2 tSize = textureSize / texture.getSize();

	_shader->enable();
	_shader->setUniformMat4("model", model);
	_shader->setUniform1i("tex", 0);
	_shader->setUniform2f("tPos", tPos);
	_shader->setUniform2f("tSize", tSize);

	texture.use(0);
	glBindVertexArray(_vertexArray);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
	glBindVertexArray(NULL);
	_shader->disable();
}
