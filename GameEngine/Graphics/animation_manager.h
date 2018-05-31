#pragma once
#include "animation.h"
#include <map>
#include <vector>

class AnimationManager
{
private:
	std::map<std::string, Animation*> _animations;
	Animation* _currentAnimation;
	Animation* _nextAnimation;
	std::vector<glm::vec2> _changeCurrentAt;
public:
	AnimationManager() : _currentAnimation(nullptr), _nextAnimation(nullptr) {}

	const Texture* getCurrentAnimationTexture() const
	{
		if (!_currentAnimation)
		{
			throw std::logic_error("No active animation set!");
		}
		return _currentAnimation->getTexture();
	}

	glm::vec2 getCurrentTextureFramePosition() const
	{
		if(!_currentAnimation)
		{
			throw std::logic_error("No active animation set!");
		}
		return _currentAnimation->getTextureFramePosition();
	}

	void makeTransition(const std::string& name, const std::vector<glm::vec2>& changeAt, const glm::vec2& startAt);
	void addAnimation(const std::string& name, Animation* animation);
	void updateAnimation(float dt);
	~AnimationManager();
};
