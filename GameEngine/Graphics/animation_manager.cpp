#include "animation_manager.h"

const Texture* AnimationManager::getCurrentAnimationTexture() const
{
	if (!_currentAnimation)
	{
		throw std::logic_error("No active animation set!");
	}
	return _currentAnimation->getTexture();
}

glm::vec2 AnimationManager::getCurrentTextureFramePosition() const
{
	if (!_currentAnimation)
	{
		throw std::logic_error("No active animation set!");
	}
	return _currentAnimation->getTextureFramePosition();
}

void AnimationManager::makeTransition(const std::string& name, const std::vector<glm::vec2>& changeAt, const glm::vec2& startAt)
{
	if(!_currentAnimation)
	{
		throw std::logic_error("No active animation set!");
	}
	
	_nextAnimation = _animations.at(name);
	_nextAnimation->setCurrentFrame(startAt);
	_changeCurrentAt = changeAt;
}

void AnimationManager::addAnimation(const std::string& name, Animation* animation)
{
	_animations[name] = animation;
	if(!_currentAnimation)
	{
		_currentAnimation = animation;
	}
}

void AnimationManager::updateAnimation(float dt)
{
	if (!_currentAnimation)
	{
		throw std::logic_error("No active animation set!");
	}
	_currentAnimation->update(dt);
	if (_nextAnimation)
	{
		for(glm::vec2 frame : _changeCurrentAt)
		{
			if(_currentAnimation->getCurrentFrame() == frame)
			{
				_currentAnimation = _nextAnimation;
				_nextAnimation = nullptr;
				break;
			}
		}
	}
}

AnimationManager::~AnimationManager()
{
	for(std::pair<std::string, Animation*> element : _animations)
	{
		delete element.second;
	}
}
