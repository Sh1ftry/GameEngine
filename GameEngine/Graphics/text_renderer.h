#pragma once
#include <glm/glm.hpp>
#include "shader.h"
#include "texture.h"
#include <string>
#include "../Utilities/font.h"

/*
 * @brief Class responsible for rendering text
 */
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
	/**
	 * @param Shader shader responsible for handling rendering
	 */
	TextRenderer(const Shader* shader);
	~TextRenderer();
	/**
	 * @brief Sets projection matrix
	 * @param projectionMatrix	projection matrix to set
	 */
	void setProjection(const glm::mat4& projectionMatrix);
	/**
	 * @brief			Draws text				
	 * @param text		text to draw
	 * @param font		font with which to draw the text
	 * @param position	vector with position
	 * @param color		color of the text
	 */
	void drawText(const std::string& text, const Font * font, glm::vec3 position, const glm::vec4& color);
};

