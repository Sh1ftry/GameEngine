#pragma once
#include "sprite.h"

class StaticSprite : public Sprite
{
private:
	Texture _texture;
	glm::vec2 _textureFramePosition;
public:
	StaticSprite(const glm::vec3& position, const glm::vec2& size, const Texture& texture)
		: Sprite(position, size), _texture(texture), _textureFramePosition(glm::vec2(0.0f, 0.0f)) {}

	void update(float dt)
	{
		/*_timeSinceLastAnimationFrame += dt;
		if (_timeSinceLastAnimationFrame > _animationFrameTime)
		{
		_timeSinceLastAnimationFrame = 0.0f;
		_texturePosition.x += _textureSize.x;
		if (_texturePosition.x > _texture.getWidht())
		{
		_texturePosition.x = 0.0f;
		_texturePosition.y = _textureSize.y;
		if (_texturePosition.y > _texture.getHeight())
		{
		_texturePosition = glm::vec2(0.0f, 0.0f);
		}
		}
		}*/
	}
};
