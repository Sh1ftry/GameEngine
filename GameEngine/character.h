#pragma once
#include "animated_sprite.h"
#include "renderer.h"
#include "resource_manager.h"

class Character : public AnimatedSprite
{
private:
	int _health;
	bool _shouldJump;
public:
	Character(float x, float y, float width, float height)
		: AnimatedSprite(glm::vec3(x, y, 0.0f), glm::vec2(width, height)), _health(0)
	{
		_shouldJump = false;
		ResourceManager::loadTexture("jungle_run.png", "jungle_run", 1, 8);
		ResourceManager::loadTexture("jungle_jump.png", "jungle_jump", 1, 4);
		const Texture* jungleRunTexture = ResourceManager::getTexture("jungle_run");
		const Texture* jungleJumpTexture = ResourceManager::getTexture("jungle_jump");
		_animations["jump_animation"] = new Animation(jungleJumpTexture, glm::vec2(0, 0), glm::vec2(3, 0), 0.6f);
		_animations["run_animation"] = new Animation(jungleRunTexture, glm::vec2(0, 0), glm::vec2(7, 0), 0.6f);
		_currentAnimation = _animations["run_animation"];
	};

	void update(float dt) override
	{
		_currentAnimation->update(dt);
		_position.x += 200 * dt;
		
		if(_currentAnimation == _animations["jump_animation"])
		{
			if(_currentAnimation->getCurrentFrame() == glm::vec2(2, 0))
			{
				_shouldJump = false;
			}
			else if(_currentAnimation->getCurrentFrame() == glm::vec2(3, 0))
			{
				_currentAnimation = _animations["run_animation"];
				_currentAnimation->setCurrentFrame(glm::vec2(5, 0));
			}

			if(_shouldJump)
			{
				_position.y += 100 * dt;
			}
			else
			{
				_position.y -= 100 * dt;
			}
		}
		
		if (_position.x >= 200 && _position.x <= 230)
		{
			_shouldJump = true;
		}

		if(_shouldJump && (_currentAnimation->getCurrentFrame() == glm::vec2(1, 0) || _currentAnimation->getCurrentFrame() == glm::vec2(5, 0)))
		{
			_currentAnimation = _animations["jump_animation"];
		}

		if (_position.y < 100) _position.y = 100;
		if (_position.x > 800) _position.x = -100;
	}

	void draw(Renderer renderer) override
	{
		renderer.draw(_position, _size, *_currentAnimation->getTexture(), _currentAnimation->getTextureFramePosition(), _currentAnimation->getTexture()->getFrameSize());
	}

	~Character() = default;
};