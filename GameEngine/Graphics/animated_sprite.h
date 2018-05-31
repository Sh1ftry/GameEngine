#pragma once
#include "sprite.h"
#include "animation_manager.h"

/*
 * @brief	Class representing animated sprite.
 *			It has an animation manager, that
 *			is used to handle animation creation,
 *			transition and destruction.
 */
class AnimatedSprite : public Sprite
{
protected:
	AnimationManager _animationManager;
public:
	AnimatedSprite(const glm::vec3& position, const glm::vec2& size)
		: Sprite(position, size) {}
	
	virtual ~AnimatedSprite() = default;
};
