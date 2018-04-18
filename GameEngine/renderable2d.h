#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "buffer.h"
#include "indexbuffer.h"
#include "vertexarray.h"
#include "shader.h"

/**
 * @brief	Class representing renderable 2d object that has
 *			position, size and color. It can be rendered using
 *			SimpleRenderer2D
 * @see		SimpleRenderer2D
 */
class Renderable2D
{
protected:
	glm::vec2 _size;
	glm::vec3 _position;
	glm::vec4 _color;
public:
	Renderable2D(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
		: _size(size), _position(position), _color(color) {}

	const glm::vec2& getSize() const
	{
		return _size;
	}

	const glm::vec3& getPosition() const
	{
		return _position;
	}

	const glm::vec4& getColor() const
	{
		return _color;
	}

	virtual ~Renderable2D() = default;
};