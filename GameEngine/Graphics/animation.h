#pragma once
#include "texture.h"
#include <glm/glm.hpp>

/*
 * @brief	Class representing an animation.
 * @details	Every animation has a texture with animation spite sheet
 *			(for now, a single animation should be on one sprite sheet),
 *			vectors with informations where the animation should start, end,
 *			and on which sprite sheet frame it is now. It also has an animation
 *			time (in seconds), which is an information on how long should whole
 *			animation (from start to end) last. In order to properly change frames
 *			it also has a field with time since last animation frame, which tells
 *			how many seconds passed since frame change.
 */
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
	
	/**
	 * @brief Creates		animation
	 * @param texture		pointer to texture (constructor does not copy the texture)
	 * @param from			from which sprite sheet frame should animation start
	 * @param to			on which sprite sheet frame should animation go back to beginning
	 * @param animationTime time from first to last frame
	 */
	Animation(const Texture* texture, const glm::vec2& from, const glm::vec2& to, float animationTime);
	
	/**
	 * @brief		Updates animation
	 * @param dt	game's tick time (time since last game's frame) 
	 */
	void update(float dt);

	/**
	 * @return		pointer to animation sprite sheet texture
	 */
	const Texture* getTexture() const
	{
		return _texture;
	}

	/**	
	 * @details		If an animation has a sprite sheet with 5 frames, and the sprite
	 *				sheet's size is 100 px x 40 px (20px x 50px per frame) and it is currently
	 *				on the second frame the function will return vector with x=20 and y=0
	 * @return		vector with current animation frame position on sprite sheet
	 */
	glm::vec2 getTextureFramePosition() const
	{
		return _currentFrame * _texture->getFrameSize();
	}

	/**
	 * @return		vector with current animation frame
	 */
	const glm::vec2& getCurrentFrame() const
	{
		return _currentFrame;
	}

	/**
	 * @brief		Sets current animation frame
	 * @param frame frame position
	 */
	void setCurrentFrame(const glm::vec2 frame)
	{
		_currentFrame = frame;
	}

	~Animation() = default;
};