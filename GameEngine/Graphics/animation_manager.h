#pragma once
#include "animation.h"
#include <map>
#include <vector>

/*
 * @brief	Class responsible for handling animation creation,
 *			transition and destruction.
 * @details	A single animation manager is responsible for handling animations for single object.
 *			It has a map, with all created animations (every animation has its name), a pointer to
 *			current animation and a pointer to next animation (if transition should occure) and a vector
 *			with frame on which a transition should start.
 *			
 *			Using this class comes down to:
 *			<ul>
 *				<ol> Creating animations and giving them names
 *				<ol> Making transitions from one animation to another
 *			</ul>
 *			
 *			Example usage of this class would be to have an object (game's character for example)
 *			with one of the fields being this class. In constructor of the character's class some animations
 *			would be created and put into animation manager (idle and run animation). In a situation
 *			when the character is starting to run the animation manager would be asked to change
 *			the idle animation to run animation and when the character would stop, the animation manager
 *			would be asked to change the animation from run to idle. Simple as that.		
 */
class AnimationManager
{
private:
	std::map<std::string, Animation*> _animations;
	Animation* _currentAnimation;
	Animation* _nextAnimation;
	std::vector<glm::vec2> _changeCurrentAt;
public:
	/**
	 * @brief	Sets current and next animations' pointers to null.
	 *			So updating the animation manager in this state would result in exeption
	 *			being thrown.
	 */
	AnimationManager() : _currentAnimation(nullptr), _nextAnimation(nullptr) {}

	/**
	 * @throws	std::logic_error if no animation is set	
	 * @return	texture with animation's sprite sheet 
	 */
	const Texture* getCurrentAnimationTexture() const;

	/**
	* @throws	std::logic_error if no animation is set
	* @return	vector with animation frame position (in pixels)
	*/
	glm::vec2 getCurrentTextureFramePosition() const;

	/**
	 * @brief			Makes transition from one animation to another
	 * @param name		name of the animation to which the transition should be
	 * @param changeAt	array with vector of frame positions on which the current animation should change
	 * @param startAt	vector with frame position on which the next animation should start
	 */
	void makeTransition(const std::string& name, const std::vector<glm::vec2>& changeAt, const glm::vec2& startAt);
	/**
	 * @brief			Adds an animation to animation manager
	 * @param name		animation's name
	 * @param animation pointer to animation
	 */
	void addAnimation(const std::string& name, Animation* animation);
	/**
	 * @brief			Updates the animation manager
	 * @param dt		time since last game's frame
	 */
	void updateAnimation(float dt);
	~AnimationManager();
};
