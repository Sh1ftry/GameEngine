#pragma once
#include "Graphics/animated_sprite.h"
#include "Graphics/renderer.h"
#include "Utilities/resource_manager.h"
#include <irrKlang/irrKlang.h>
#include "Graphics/window.h"
#include "MapManager.h"
#include <GLFW/glfw3.h>
#include "tile.h"
#include "TheGame.h"

/**
* @brief Class Character2 represents PC - Player character
*/

class Character2 : public AnimatedSprite
{
private:
	int _facing;
	bool _walking;
	bool _left;
	bool _down;
	bool _up;
	bool _right;
	float _Xvelocity;
	float _YVelocity;
	float _time;
	int _start_x;
	int _start_y;
	int _pos_x;
	int _pos_y;
	bool _transition;
	bool _back;
	bool _dialogue;
	bool _z;
	bool _theGame;
	irrklang::ISoundEngine* _soundEngine;
	MapManager* _manager;
public:
	Character2();

	Character2(float x, float y, float width, float height, MapManager* manager, irrklang::ISoundEngine* soundEngine)
		: AnimatedSprite(glm::vec3(x, y, 0.0f), glm::vec2(width, height)), _soundEngine(soundEngine)
	{
		_facing = 2;
		_walking = false;
		_left = false;
		_right = false;
		_up = false;
		_down = false;
		_Xvelocity = 0;
		_YVelocity = 0;
		_time = 0.0f;
		_start_x = x;
		_start_y = y;
		_pos_x = x / 32;
		//_pos_y = 13;
		_pos_y = y / 32;
		_transition = false;
		_manager = manager;
		_back = false;
		_dialogue = false;
		_z = false;
		_theGame = false;

		
		_animationManager.addAnimation("move_up", new Animation(ResourceManager::getTexture("animations"), glm::vec2(0, 3), glm::vec2(2, 3), 0.5f));
		_animationManager.addAnimation("move_right", new Animation(ResourceManager::getTexture("animations"), glm::vec2(0, 2), glm::vec2(2, 2), 0.5f));
		_animationManager.addAnimation("move_down", new Animation(ResourceManager::getTexture("animations"), glm::vec2(0, 1), glm::vec2(2, 1), 0.5f));
		_animationManager.addAnimation("move_left", new Animation(ResourceManager::getTexture("animations"), glm::vec2(0, 0), glm::vec2(2, 0), 0.5f));
		//_animationManager.addAnimation("stand", new Animation(ResourceManager::getTexture("animations"), glm::vec2(1, 1), glm::vec2(1, 1), 2.f));
		_animationManager.addAnimation("stand_down", new Animation(ResourceManager::getTexture("animations"), glm::vec2(1, 1), glm::vec2(1, 1), 0.5f));
		_animationManager.addAnimation("stand_right", new Animation(ResourceManager::getTexture("animations"), glm::vec2(1, 2), glm::vec2(1, 2), 0.5));
		_animationManager.addAnimation("stand_left", new Animation(ResourceManager::getTexture("animations"), glm::vec2(1, 0), glm::vec2(1, 0), 0.5f));
		_animationManager.addAnimation("stand_up", new Animation(ResourceManager::getTexture("animations"), glm::vec2(1, 3), glm::vec2(1, 3), 0.5f));
		animation_change("stand_down", glm::vec2(1, 1));
	}
	/**
	* @brief moving character one tile up
	*/
	void go_up()
	{
		if(!_walking && (*_manager)(_pos_x, _pos_y + 1)->is_passable())
		{
			_walking = true;
			_up = true;
			_facing = 8;
			_down = false;
			_left = false;
			_right = false;
			_YVelocity = 100;
			_Xvelocity = 0;
			//_animationManager.makeTransition("move_up", { glm::vec2(0,0), glm::vec2(0,1),glm::vec2(0,2),glm::vec2(0,3), glm::vec2(1, 1) }, glm::vec2(0, 3));
			animation_change("move_up", glm::vec2(0, 3));
		}
	}
	/**
	* @brief moving character one tile right
	*/
	void go_right()
	{
		if (!_walking && (*_manager)(_pos_x + 1, _pos_y)->is_passable())
		{
			_walking = true;
			_up = false;
			_down = false;
			_left = false;
			_right = true;
			_facing = 6;
			_YVelocity = 0;
			_Xvelocity = 100;
			//_animationManager.makeTransition("move_right", { glm::vec2(0,0), glm::vec2(0,1),glm::vec2(0,2),glm::vec2(0,3), glm::vec2(1, 1) }, glm::vec2(0, 2));
			animation_change("move_right", glm::vec2(0, 2));
		}
	}
	/**
	* @brief moving character one tile down
	*/
	void go_down()
	{
		if (!_walking && (*_manager)(_pos_x, _pos_y - 1)->is_passable())
		{
			_walking = true;
			_up = false;
			_down = true;
			_facing = 2;
			_left = false;
			_right = false;
			_YVelocity = -100;
			_Xvelocity = 0;
			//_animationManager.makeTransition("move_down", { glm::vec2(0,0), glm::vec2(0,1),glm::vec2(0,2),glm::vec2(0,3), glm::vec2(1, 1) }, glm::vec2(0, 1));
			animation_change("move_down", glm::vec2(0, 1));
		}
	}
	/**
	* @brief moving character one tile left
	*/
	void go_left()
	{
		if (!_walking && (*_manager)(_pos_x - 1, _pos_y)->is_passable())
		{
			_walking = true;
			_up = false;
			_down = false;
			_left = true;
			_facing = 4;
			_right = false;
			_YVelocity = 0;
			_Xvelocity = -100;
			//_animationManager.makeTransition("move_left", { glm::vec2(0,0), glm::vec2(0,1),glm::vec2(0,2),glm::vec2(0,3), glm::vec2(1, 1) }, glm::vec2(0, 0));
			animation_change("move_left", glm::vec2(0, 0));
		}
	}
	/**
	* @brief rotate character to face specified direction
	* @param facing direction to face
	*/
	void rotate(int facing)
	{
		switch(facing)
		{
		case 2:
			animation_change("stand_left", glm::vec2(1, 0));
			_facing = facing;
			break;
		case 4:
			animation_change("stand_down", glm::vec2(1, 1));
			_facing = facing;
			break;
		case 6:
			animation_change("stand_right", glm::vec2(1, 2));
			_facing = facing;
			break;
		case 8:
			animation_change("stand_up", glm::vec2(1, 3));
			_facing = facing;
			break;
		default:
			break;
		}
	}
	/**
	* @brief calling out interact method from MapObject at which character is facing
	*/
	void interact()
	{
		if (!_walking && _facing == 4)
			_dialogue = (*_manager)(_pos_x - 1, _pos_y)->interact();
		else if (!_walking && _facing == 2)
			_dialogue = (*_manager)(_pos_x, _pos_y - 1)->interact();
		else if (!_walking && _facing == 6)
			_dialogue = (*_manager)(_pos_x + 1, _pos_y)->interact();
		else if(!_walking && _facing == 8)
			_dialogue = (*_manager)(_pos_x, _pos_y + 1)->interact();
	}
	/**
	* @brief if called MapObject has a dialogues lines, this function loads the next one
	*/
	void load_next_line() const
	{
		if (!_walking && _facing == 4)
			(*_manager)(_pos_x - 1, _pos_y)->next_line();
		else if (!_walking && _facing == 2)
			(*_manager)(_pos_x, _pos_y - 1)->next_line();
		else if (!_walking && _facing == 6)
			(*_manager)(_pos_x + 1, _pos_y)->next_line();
		else if (!_walking && _facing == 8)
			(*_manager)(_pos_x, _pos_y + 1)->next_line();
	}

	void handleInput(const Window& window)
	{
		
		bool _ctrl = false;
		if (window.isKeyboardKeyPressed(GLFW_KEY_LEFT_CONTROL)) _ctrl = true;
		if (!_ctrl && window.isKeyboardKeyPressed(GLFW_KEY_LEFT) && !_dialogue) go_left();
		if (!_ctrl && window.isKeyboardKeyPressed(GLFW_KEY_RIGHT) && !_dialogue) go_right();
		if (!_ctrl &&window.isKeyboardKeyPressed(GLFW_KEY_DOWN) && !_dialogue) go_down();
		if (!_ctrl &&window.isKeyboardKeyPressed(GLFW_KEY_UP) && !_dialogue) go_up();
		if (_ctrl && window.isKeyboardKeyPressed(GLFW_KEY_UP) && !_dialogue) rotate(8);
		if (_ctrl && window.isKeyboardKeyPressed(GLFW_KEY_RIGHT) && !_dialogue) rotate(6);
		if (_ctrl && window.isKeyboardKeyPressed(GLFW_KEY_DOWN) && !_dialogue) rotate(4);
		if (_ctrl && window.isKeyboardKeyPressed(GLFW_KEY_LEFT) && !_dialogue) rotate(2);
		if (!_ctrl && window.isKeyboardKeyPressed(GLFW_KEY_Z) && !_dialogue) interact();
		else if (!_ctrl && window.isKeyboardKeyPressed(GLFW_KEY_Z) && _dialogue && !_z) load_next_line();
		if (!_ctrl && window.isKeyboardKeyPressed(GLFW_KEY_X) && _dialogue)
		{
			_dialogue = false;
			load_next_line();
		}
		if(window.isKeyboardKeyPressed(GLFW_KEY_Z))	_z = true;
		if (!window.isKeyboardKeyPressed(GLFW_KEY_Z)) _z = false;
	}

	void update(float dt) override
	{
		_animationManager.updateAnimation(dt);
		_position.x += _Xvelocity * dt;
		_position.y += _YVelocity * dt;
		if (_walking && !_dialogue)
		{
			if(_left && ((_start_x - _position.x) >= 32))
			{
				_start_x -= 32;
				_position.x = _start_x;
				_walking = false;
				_left = false;
				_Xvelocity = 0;
				_pos_x--;
				//_animationManager.makeTransition("stand", { glm::vec2(0,0), glm::vec2(0,1),glm::vec2(0,2),glm::vec2(0,3), glm::vec2(1, 1) }, glm::vec2(1, 1));
				animation_change("stand_left", glm::vec2(1, 0));
				if ((*_manager)(_pos_x, _pos_y)->on_pass(_soundEngine))
				{
					_back = (*_manager)(_pos_x, _pos_y)->back();
					_transition = true;
				}
			}
			else if(_right && ((_position.x - _start_x) >= 32))
			{
				_start_x += 32;
				_position.x = _start_x;
				_walking = false;
				_right = false;
				_Xvelocity = 0;
				_pos_x++;
				//_animationManager.makeTransition("stand", { glm::vec2(0,0), glm::vec2(0,1),glm::vec2(0,2),glm::vec2(0,3), glm::vec2(1, 1) }, glm::vec2(1, 1));
				animation_change("stand_right", glm::vec2(1, 2));
				if ((*_manager)(_pos_x, _pos_y)->on_pass(_soundEngine))
				{
					_back = (*_manager)(_pos_x, _pos_y)->back();
					_transition = true;
				}

			}
			else if(_up && ((_position.y - _start_y) >= 32))
			{
				_YVelocity = 0;
				_start_y += 32;
				_position.y = _start_y;
				_walking = false;
				_up = false;
				_pos_y++;
				animation_change("stand_up", glm::vec2(1, 3));
				if ((*_manager)(_pos_x, _pos_y)->on_pass(_soundEngine))
				{
					_back = (*_manager)(_pos_x, _pos_y)->back();
					_transition = true;
				}
			}
			else if(_down && ((_start_y - _position.y) >= 32))
			{
				_YVelocity = 0;
				_start_y -= 32;
				_position.y = _start_y;
				_walking = false;
				_down = false;
				_pos_y--;
				animation_change("stand_down", glm::vec2(1, 1));
				if ((*_manager)(_pos_x, _pos_y)->on_pass(_soundEngine))
				{
					_back = (*_manager)(_pos_x, _pos_y)->back();
					_transition = true;
				}
			}
		}
		if ((_pos_x == 12 || _pos_x == 13) && _pos_y == 17 && _manager->map_no() == 3) _theGame = true;
	}

	void animation_change(const std::string &name, const glm::vec2& frame_start)
	{
		_animationManager.makeTransition(name,
			{ glm::vec2(0,0), glm::vec2(0,1),glm::vec2(0,2),glm::vec2(0,3), glm::vec2(1, 0), glm::vec2(1,1), glm::vec2(1,2), glm::vec2(1,3), glm::vec2(2,0), glm::vec2(2,1), glm::vec2(2,2), glm::vec2(2,3), glm::vec2(3,0), glm::vec2(3,1), glm::vec2(3,2), glm::vec2(3,3) },
			frame_start);
	}

	void draw(Renderer renderer) override
	{
		renderer.draw(_position, _size, *_animationManager.getCurrentAnimationTexture(),
			_animationManager.getCurrentTextureFramePosition(), _animationManager.getCurrentAnimationTexture()->getFrameSize(), false);
		
	}
	
	const glm::vec2& getPosition()
	{
		return _position;
	}

	bool transition() const
	{
		return _transition;
	}

	bool back() const
	{
		return _back;
	}

	bool theGame() const
	{
		return _theGame;
	}

	bool dialogue() const
	{
		return _dialogue;
	}
	/**
	* @brief preparing character to move to the next map
	* @param to_x x position of where character should spawn in the next map
	* @param to_y y position of where character should spawn in the next map
	*/
	void set_transition(unsigned int to_x, unsigned int to_y)
	{
		_pos_x = to_x;
		_pos_y = to_y;
		_position.x = (to_x * 32);
		_position.y = (to_y * 32);
		_start_x = _position.x;
		_start_y = _position.y;
		_transition = false;
		if (!_back)
			_manager->load_next_map();
		else
			_manager->load_prev_map();
	}

	~Character2() = default;
};

