#pragma once
#include <glm/glm.hpp>
#include "shader.h"
#include "texture.h"
#include <string>
#include "../Utilities/font.h"

/**
 * @brief Class responsible for rendering sprites
 */
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
	glm::mat4 _projection;
public:
	Renderer();
	~Renderer();
	/**
	 * @brief Activates shader
	 * @param shader shader to activate
	 */
	void useShader(Shader* shader);
	/**
	 * @brief Sets projection matrix
	 * @param projectionMatrix projection matrix to set
	 */
	void setProjection(const glm::mat4& projectionMatrix);
	/**
	 * @brief Draws sprite 
	 * @param position	position where to draw sprite
	 * @param size		size of the sprite
	 * @param color		color of the sprite
	 */
	//void draw(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) const;
	/**
	 * @brief Draws textured sprite
	 * @param position	position where to draw sprite
	 * @param size		size of the sprite
	 * @param texture	sprite sheet
	 * @param texturePosition	coordinates of the texture on the sprite sheet
	 * @param textureSize		size of the texture
	 * @param flipVert			should flip vertical while drawing
	 * @param flipHoriz			should flip horizontal while drawing
	 */
	void draw(const glm::vec3& position, const glm::vec2& size, const Texture& texture, const glm::vec2& texturePosition, const glm::vec2& textureSize, bool flipVert = false, bool flipHoriz = false) const;
	/**
	* @brief			Draws text
	* @param text		text to draw
	* @param font		font with which to draw the text
	* @param position	vector with position
	* @param color		color of the text
	*/
	void drawText(const std::string& text, const Font * font, glm::vec3 position, const glm::vec4& color) const;
};