#include "text_renderer.h"
#include <glm/gtc/matrix_transform.hpp>

TextRenderer::TextRenderer(const Shader* shader)
	: _shader(shader)
{
	GLuint vertexBuffer;
	GLuint _elementBuffer;
	GLushort indexes[] = { 0, 1, 2, 2, 3, 0 };
	GLfloat vertices[] =
	{
		0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f, 0.0f
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

TextRenderer::~TextRenderer()
{
	//glDeleteVertexArrays()
}

void TextRenderer::setProjection(const glm::mat4 & projectionMatrix)
{
	_shader->enable();
	_shader->setUniformMat4("projection", projectionMatrix);
}

void TextRenderer::drawText(const std::string& text, const Font * font, glm::vec3 position, const glm::vec4& color)
{
	_shader->enable();
	for (char c : text)
	{
		const Font::Character& character = font->getCharacter(c);

		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(position.x + character._bearing.x, position.y - (character.size.y - character._bearing.y), 0.0f));
		model = glm::scale(model, glm::vec3(character.size, 1.0f));

		_shader->setUniformMat4("model", model);
		_shader->setUniform1i("tex", 0);
		_shader->setUniform4f("col", color);

		character.texture->use(0);
		glBindVertexArray(_vertexArray);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
		glBindVertexArray(NULL);
		position.x += (character.advance >> 6);
	}
	_shader->disable();
}
