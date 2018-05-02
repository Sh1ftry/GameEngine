#pragma once
#include <glm/glm.hpp>
#include "shader.h"
#include "texture.h"

class Renderer
{
private:
	struct VertexData
	{
		glm::vec3 position;
		glm::vec2 texturePosition;
	};
	GLuint _vertexArray;
	Shader* _shader;
public:
	Renderer(Shader* shader);
	~Renderer();
	void draw(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
	void draw(const glm::vec3& position, const glm::vec2& size, const Texture& texture, const glm::vec2& texturePosition, const glm::vec2& textureSize);
};
