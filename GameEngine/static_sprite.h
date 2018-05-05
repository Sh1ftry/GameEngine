#pragma once
#include "sprite.h"

class StaticSprite : public Sprite
{
protected:
	const Texture* _texture;
	glm::vec2 _textureFramePosition;
public:
	StaticSprite(const glm::vec3& position, const glm::vec2& size, const Texture* texture, const glm::vec2& textureFramePosition = glm::vec2(0.0f))
		: Sprite(position, size), _texture(texture), _textureFramePosition(textureFramePosition) {}

	virtual void update(float dt) = 0;
	virtual void draw(Renderer renderer) = 0;

	virtual ~StaticSprite() = default;
};
