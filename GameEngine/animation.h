#pragma once
#include "texture.h"
#include <glm/glm.hpp>

class Animation
{
private:
	const Texture* _texture;
	glm::vec2 _from;
	glm::vec2 _to;
	glm::vec2 _currentFrame;
	float _animationFrameTime;
	float _timeSinceLastAnimationFrame;
public:
	Animation(const Texture* texture, const glm::vec2& from, const glm::vec2& to, float animationTime);
	
	void update(float dt);

	const Texture* getTexture() const
	{
		return _texture;
	}

	glm::vec2 getTextureFramePosition() const
	{
		return _currentFrame * _texture->getFrameSize();
	}

	const glm::vec2& getCurrentFrame() const
	{
		return _currentFrame;
	}

	void setCurrentFrame(const glm::vec2 frame)
	{
		_currentFrame = frame;
	}

	~Animation() = default;
};