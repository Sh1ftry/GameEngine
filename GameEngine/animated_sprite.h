#pragma once
#include "sprite.h"
#include <map>
#include "animation.h"

class AnimatedSprite : public Sprite
{
protected:
	std::map<std::string, Animation*> _animations;
	Animation* _currentAnimation;
public:
	AnimatedSprite(const glm::vec3& position, const glm::vec2& size)
		: Sprite(position, size) {}
	
	void addAnimation(const std::string& name, const Animation& animation)
	{
		_animations[name] = new Animation(animation);
	}

	virtual ~AnimatedSprite() = default;
};
