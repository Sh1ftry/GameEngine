#pragma once
#include "Graphics/static_sprite.h"
#include "Graphics/renderer.h"

/**
* @brief class represents a single texture in the game
*/

class Tile : public StaticSprite
{
public:
	Tile(const glm::vec3& position, const glm::vec2& size, const Texture* texture, const glm::vec2& textureFramePosition = glm::vec2(0.0f))
		: StaticSprite(position, size, texture, textureFramePosition) {}

	void setPosition(const glm::vec3& newPos)
	{
		_position = newPos;
	}

	const glm::vec3& getPosition() const
	{
		return _position;
	}
	
	void setTextureFramePosition(const glm::vec2& textureFramePosition)
	{
		_textureFramePosition = textureFramePosition;
	}
	void update(float dt) override {}
	void draw(Renderer renderer) override
	{
		renderer.draw(_position, _size, *_texture, _textureFramePosition * _texture->getFrameSize(), _texture->getFrameSize());
	}
	~Tile() override = default;
};
