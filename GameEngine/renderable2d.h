#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "buffer.h"
#include "indexbuffer.h"
#include "vertexarray.h"
#include "shader.h"
#include "texture.h"

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
	
	glm::vec2 _texturePosition;
	glm::vec2 _textureSize;
	float _animationFrameTime;
	float _timeSinceLastAnimationFrame;
	Texture _texture;
public:
	Renderable2D(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const Texture& texture)
		: _size(size), _position(position), _color(color), _texture(texture)
	{
		_textureSize.x = (float)_texture.getWidht() / _texture.getCols();
		_textureSize.y = (float)_texture.getHeight() / _texture.getRows();
		_animationFrameTime = 0.7f / (texture.getCols() * texture.getRows());
		_timeSinceLastAnimationFrame = 0.0f;
		_texturePosition = glm::vec2(0.0f, 0.0f);
	}

	void update(float dt)
	{
		_timeSinceLastAnimationFrame += dt;
		if(_timeSinceLastAnimationFrame > _animationFrameTime)
		{
			_timeSinceLastAnimationFrame = 0.0f;
			_texturePosition.x += _textureSize.x;
			if(_texturePosition.x > _texture.getWidht())
			{
				_texturePosition.x = 0.0f;
				_texturePosition.y = _textureSize.y;
				if(_texturePosition.y > _texture.getHeight())
				{
					_texturePosition = glm::vec2(0.0f, 0.0f);
				}
			}
		}
	}

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

	const Texture& getTexture() const
	{
		return _texture;
	}

	const glm::vec2& getTexturePosition() const
	{
		return _texturePosition;
	}

	const glm::vec2& getTextureSize() const
	{
		return _textureSize;
	}


	virtual ~Renderable2D() = default;
};