#pragma once
#include <glm/glm.hpp>
#include "shader.h"
#include "texture.h"
#include <string>
#include "font.h"

class Renderer
{
private:
	struct VertexData
	{
		glm::vec3 position;
		glm::vec2 texturePosition;
	};
	GLuint _vertexArray;
	const Shader* _shader;
public:
	Renderer(const Shader* shader);
	~Renderer();
	void setProjection(const glm::mat4& projectionMatrix);
	void draw(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
	void draw(const glm::vec3& position, const glm::vec2& size, const Texture& texture, const glm::vec2& texturePosition, const glm::vec2& textureSize);
};

class TextRenderer
{
private:
	struct VertexData
	{
		glm::vec3 position;
		glm::vec2 texturePosition;
	};
	GLuint _vertexArray;
	const Shader* _shader;
public:
	TextRenderer(const Shader* shader);
	~TextRenderer();
	void setProjection(const glm::mat4& projectionMatrix);
	void drawText(const std::string& text, const Font * font, glm::vec3 position, const glm::vec4& color);
};
