#pragma once
#include <glm/glm.hpp>
#include "texture.h"

class Renderer;

/**
* @brief	Class representing renderable 2d object that has
*			position, size and color. It can be rendered using
*			SimpleRenderer2D
* @see		SimpleRenderer2D
*/
class Sprite
{
protected:
	glm::vec2 _size;
	glm::vec3 _position;
public:
	Sprite(const glm::vec3& position, const glm::vec2& size)
		: _size(size), _position(position) {}

	Sprite(const Sprite& sprite) = default;
	Sprite(Sprite&& sprite) = default;
	Sprite& operator=(const Sprite& sprite) = default;
	Sprite& operator=(Sprite&& sprite) = default;

	virtual void update(float dt) = 0;
	virtual void draw(Renderer renderer) = 0;
	
	virtual ~Sprite() = default;
};