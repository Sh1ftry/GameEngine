#pragma once
#include "Graphics/animated_sprite.h"
#include "Graphics/renderer.h"
#include "Utilities/resource_manager.h"
#include <irrKlang/irrKlang.h>

class Character : public AnimatedSprite
{
private:
	int _health;
	float _gravity;
	bool _jumping;
	bool _falling;
	bool _left;
	bool _stopped;
	float _velocity;
	float _runningVelocity;
	float _time;
	float _soundTime;
	bool _running;
	irrklang::ISoundEngine* _soundEngine;
public:
	Character(float x, float y, float width, float height, irrklang::ISoundEngine* soundEngine)
		: AnimatedSprite(glm::vec3(x, y, 0.0f), glm::vec2(width, height)), _health(0), _soundEngine(soundEngine)
	{
		_time = 0.0f;
		_soundTime = 0.0f;
		_jumping = false;
		_falling = false;
		_running = false;
		_left = false;
		_stopped = true;
		_gravity = 900;
		_velocity = 0;
		_runningVelocity = 0;
		ResourceManager::loadTexture("Resources/jungle_run.png", "jungle_run", 1, 8);
		ResourceManager::loadTexture("Resources/jungle_jump.png", "jungle_jump", 1, 2);
		ResourceManager::loadTexture("Resources/jungle_idle.png", "jungle_idle", 1, 12);
		const Texture* jungleRunTexture = ResourceManager::getTexture("jungle_run");
		const Texture* jungleJumpTexture = ResourceManager::getTexture("jungle_jump");
		const Texture* jungleIdleTexture = ResourceManager::getTexture("jungle_idle");
		_animationManager.addAnimation("idle_animation", new Animation(jungleIdleTexture, glm::vec2(0, 0), glm::vec2(11, 0), 0.8f));
		_animationManager.addAnimation("run_animation", new Animation(jungleRunTexture, glm::vec2(0, 0), glm::vec2(7, 0), 0.6f));
		_animationManager.addAnimation("jump_animation", new Animation(jungleJumpTexture, glm::vec2(0, 0), glm::vec2(1, 0), 0.3f));
	}

	void jump()
	{
		if (!_jumping && !_falling)
		{
			_jumping = true;
			_stopped = false;
			_velocity = 300;
			_animationManager.makeTransition("jump_animation", { glm::vec2(3, 0), glm::vec2(7, 0) }, glm::vec2(0, 0));
		}
	}

	void goLeft()
	{
		if((!_left && !_jumping && !_falling) || _stopped)
		{
			if(!_running) _animationManager.makeTransition("run_animation", { glm::vec2(0,0) }, glm::vec2(0, 0));
			_running = true;
			_left = true;
			_stopped = false;
			_runningVelocity = -200;
		}
		
	}

	void goRight()
	{
		if((_left && !_jumping && !_falling) || _stopped)
		{
			if (!_running) _animationManager.makeTransition("run_animation", { glm::vec2(0,0) }, glm::vec2(0, 0));
			_running = true;
			_left = false;
			_stopped = false;
			_runningVelocity = 200;
		}
	}

	void stop()
	{
		if (!_falling && !_jumping)
		{
			_animationManager.makeTransition("idle_animation", { glm::vec2(0,0), glm::vec2(2,0), glm::vec2(4,0), glm::vec2(6,0) }, glm::vec2(3, 0));
			_running = false;
			_stopped = true;
			_runningVelocity = 0;
		}
	}

	void handleInput(const Window& window)
	{
		if (window.isKeyboardKeyPressed(GLFW_KEY_LEFT)) goLeft();
		else if (window.isKeyboardKeyPressed(GLFW_KEY_RIGHT)) goRight();
		else if(window.isKeyboardKeyPressed(GLFW_KEY_DOWN)) stop();
		if (window.isKeyboardKeyPressed(GLFW_KEY_SPACE)) jump();
	}

	void update(float dt) override
	{
		_animationManager.updateAnimation(dt);
		_position.x += _runningVelocity * dt;

		/*if (_position.x >= 100 && _position.x <= 130)
		{
		jump();
		}*/

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
		else if (_falling)
		{
			_position.y -= _velocity * dt;
			_velocity += _gravity * dt;
			if (_position.y < 80)
			{
				_velocity = 0;
				if (_runningVelocity != 0)
					_animationManager.makeTransition("run_animation", { glm::vec2(1,0) }, glm::vec2(0, 0));
				else
				{
					_animationManager.makeTransition("idle_animation", { glm::vec2(0,0), glm::vec2(2,0), glm::vec2(4,0), glm::vec2(6,0) }, glm::vec2(3, 0));
					_stopped = true;
				}
				_falling = false;
				_position.y = 80;
			}
		}

		if (!_jumping && !_falling && !_stopped)
		{
			if (_soundTime > 0.4f)
			{
				_soundTime = 0.0f;
				_soundEngine->play2D("Resources/Fantozzi-SandL2.flac", GL_FALSE);
			}
		}

		if (_position.x > 800) _position.x = -100;
		else if (_position.x < -100) _position.x = 800;
		_time += dt;
		_soundTime += dt;
		if (_time > 0.6f)
		{
			_time = 0.0f;
		}
	}

	void draw(Renderer renderer) override
	{
		renderer.draw(_position, _size, *_animationManager.getCurrentAnimationTexture(),
			_animationManager.getCurrentTextureFramePosition(), _animationManager.getCurrentAnimationTexture()->getFrameSize(), _left);
	}

	const glm::vec2& getPosition()
	{
		return _position;
	}

	~Character() = default;
};