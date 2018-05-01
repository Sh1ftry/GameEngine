#pragma once
#include <glm/glm.hpp>
#include "renderable2d.h"

class Renderer
{
private:
	struct VertexData
	{
		glm::vec3 position;
		glm::vec4 color;
	};
	GLuint _vertexArray;
	Shader* _shader;
public:
	Renderer(Shader* shader);
	~Renderer();
	void draw(const Renderable2D& renderable) const;
};