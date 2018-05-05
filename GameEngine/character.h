#pragma once
#include "animated_sprite.h"
#include "renderer.h"
#include "resource_manager.h"
#include <irrKlang/irrKlang.h>

class Character : public AnimatedSprite
{
private:
	int _health;
	float _gravity;
	bool _jumping;
	bool _falling;
	float _velocity;
	float _time;
	float _soundTime;
	irrklang::ISoundEngine* _soundEngine;
public:
	Character(float x, float y, float width, float height, irrklang::ISoundEngine* soundEngine)
		: AnimatedSprite(glm::vec3(x, y, 0.0f), glm::vec2(width, height)), _health(0), _soundEngine(soundEngine)
	{
		_time = 0.0f;
		_soundTime = 0.0f;
		_jumping = false;
		_falling = false;
		_gravity = 900;
		_velocity = 0;
		ResourceManager::loadTexture("jungle_run.png", "jungle_run", 1, 8);
		ResourceManager::loadTexture("jungle_jump.png", "jungle_jump", 1, 2);
		const Texture* jungleRunTexture = ResourceManager::getTexture("jungle_run");
		const Texture* jungleJumpTexture = ResourceManager::getTexture("jungle_jump");
		_animationManager.addAnimation("run_animation", new Animation(jungleRunTexture, glm::vec2(0, 0), glm::vec2(7, 0), 0.6f));
		_animationManager.addAnimation("jump_animation", new Animation(jungleJumpTexture, glm::vec2(0, 0), glm::vec2(1, 0), 0.3f));
	};

	void update(float dt) override
	{
		_animationManager.updateAnimation(dt);
		_position.x += 400 * dt;
		
		if (_position.x >= 100 && _position.x <= 130)
		{
			_velocity = 300;
			_jumping = true;
			_animationManager.makeTransition("jump_animation", { glm::vec2(3, 0), glm::vec2(7, 0) }, glm::vec2(0, 0));
		}

		if (_jumping)
		{
			_position.y += _velocity * dt;
			_velocity -= _gravity * dt;
			if (_velocity <= 0)
			{
				_jumping = false;
				_falling = true;
			}
		}
		else if(_falling)
		{
			_position.y -= _velocity * dt;
			_velocity += _gravity * dt;
			if (_position.y < 80)
			{
				_velocity = 0;
				_animationManager.makeTransition("run_animation", { glm::vec2(1, 0) }, glm::vec2(0, 0));
				_falling = false;
				_position.y = 80;
			}
		}

		if (!_jumping && !_falling)
		{
			if(_soundTime > 0.3f)
			{
				_soundTime = 0.0f;
				_soundEngine->play2D("Fantozzi-SandL2.flac", GL_FALSE);
			}
		}

		if (_position.x > 800) _position.x = -100;
		_time += dt;
		_soundTime += dt;
		if(_time > 0.6f)
		{
			_time = 0.0f;
		}
	}

	void draw(Renderer renderer) override
	{
		renderer.draw(_position, _size, *_animationManager.getCurrentAnimationTexture(),
			_animationManager.getCurrentTextureFramePosition(), _animationManager.getCurrentAnimationTexture()->getFrameSize());
	}

	~Character() = default;
};
