#pragma once
#include "animated_sprite.h"
#include "renderer.h"

class Character : public AnimatedSprite
{
private:
	int _health;
public:
	Character(float x, float y, float width, float height, const Animation& animation, const std::string& animationName)
		: AnimatedSprite(glm::vec3(x, y, 0.0f), glm::vec2(width, height), animation, animationName), _health(0) {};

	void update(float dt) override
	{
		_currentAnimation->update(dt);
	}

	void draw(Renderer renderer) override
	{
		renderer.draw(_position, _size, *_currentAnimation->getTexture(), _currentAnimation->getTextureFramePosition(), _currentAnimation->getTexture()->getFrameSize());
	}

	~Character() = default;
};