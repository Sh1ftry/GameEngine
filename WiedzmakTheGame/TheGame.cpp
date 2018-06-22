#include "TheGame.h"
#include "Utilities/resource_manager.h"
#include <GLFW/glfw3.h>
#include "ExitState.h"


TheGame::TheGame(irrklang::ISoundEngine* soundEngine) : _soundEngine(soundEngine)
{
	_key_pressed = true;
	_velocity = 0;
	_acceleration = 0;
	_active_option = 0;
	_action_chosen = false;
	_attack = false;
	_defend = false;
	_target_enemy1 = false;
	_target_enemy2 = false;
	_golem_1_turn = false;
	_golem_2_turn = false;
	_hero_animation = false;
	_hero_turn = true;
	_dramatic_stop = false;
	_golem_1_animation = false;
	_golem_2_animation = false;

	_tiles.push_back(new Tile(glm::vec3(0, 0, -0.9f), glm::vec2(800, 640), ResourceManager::getTexture("arena")));

	_soundEngine->stopAllSounds();
	_soundEngine->play2D("Resources/music/theme_of_happy_heart.ogg", GL_TRUE);

	auto golem = ResourceManager::getTexture("mountain");
	auto hero = ResourceManager::getTexture("animations");

	_tiles.push_back(new Tile(glm::vec3(6 * 32, 11 * 32, 0), glm::vec2(32, 64), golem, glm::vec2(13, 0)));
	_tiles.push_back(new Tile(glm::vec3(10 * 32, 11 * 32, 0), glm::vec2(32, 64), golem, glm::vec2(13, 0)));

	_tiles.push_back(new Tile(glm::vec3(8 * 32, 6 * 32, 0), glm::vec2(32, 36), hero, glm::vec2(1, 1)));

	_golem_1 = new Golem();
	_golem_2 = new Golem();

	_Hero = new Hero();
}

TheGame::~TheGame()
{
	for(Tile* tile : _tiles)
	{
		delete tile;
	}
	delete _golem_1;
	delete _golem_2;
	delete _Hero;
}

void TheGame::update(GameStateManager& gameStateManager, float dt)
{
	/*
	if(!_hero_turn)
	_time += dt;
	if (_time > 1.f)
	{
		_hero_turn = true;
		_time = 0;
	}
	*/
	
	if(_hero_turn && _action_chosen && (_attack || _defend))
	{
		if(_defend)
		{
			_Hero->_defending= true;
			_defend = false;
			_action_chosen = false;
			_attack = false;
			_hero_turn = false;
			_active_option = 0;
			_golem_1_turn = true;
		}
		if(_attack && !_dramatic_stop && (_target_enemy1 || _target_enemy2))
		{
			_acceleration = 25;
			_velocity += _acceleration * dt;
			glm::vec3 pos = _tiles[3]->getPosition();
			pos.y += _velocity * dt;
			if(pos.y > 8*32)
			{
				pos.y = 8 * 32;
				_acceleration = 0;
				_velocity = 0;
				_dramatic_stop = true;
				_soundEngine->play2D("Resources/rpg_sound_pack/RPG_Sound_Pack/battle/swing.wav", GL_FALSE);
			}
			_tiles[3]->setPosition(pos);
		}
		if(_attack && _dramatic_stop && (_target_enemy1 || _target_enemy2))
		{
			_acceleration = -25;
			_velocity += _acceleration * dt;
			glm::vec3 pos = _tiles[3]->getPosition();
			pos.y += _velocity * dt;
			if(pos.y < 6*32)
			{
				pos.y = 6 * 32;
				_acceleration = 0;
				_velocity = 0;
				_dramatic_stop = false;
				_hero_turn = false;
				if (_target_enemy1)
					_golem_1->take_hit(_Hero->_attack);
				else _golem_2->take_hit(_Hero->_attack);
				_soundEngine->play2D("Resources/rpg_sound_pack/RPG_Sound_Pack/NPC/ogre/ogre3.wav", GL_FALSE);
				_active_option = 0;
				_defend = false;
				_action_chosen = false;
				_attack = false;
				_hero_turn = false;
				_golem_1_turn = true;
				_target_enemy1 = false;
				_target_enemy2 = false;
			}
			_tiles[3]->setPosition(pos);
		}
	}
	else if (_golem_1_turn)
	{
		if (!_dramatic_stop)
		{
			_acceleration = -25;
			_velocity += _acceleration * dt;
			glm::vec3 pos = _tiles[1]->getPosition();
			pos.y += _velocity * dt;
			if (pos.y < 9 * 32)
			{
				pos.y = 9 * 32;
				_acceleration = 0;
				_velocity = 0;
				_dramatic_stop = true;
				_soundEngine->play2D("Resources/rpg_sound_pack/RPG_Sound_Pack/NPC/gutteral beast/mnstr3.wav", GL_FALSE);
			}
			_tiles[1]->setPosition(pos);
		}
		else
		{
			_acceleration = 25;
			_velocity += _acceleration * dt;
			glm::vec3 pos = _tiles[1]->getPosition();
			pos.y += _velocity * dt;
			if (pos.y > 11*32)
			{
				pos.y = 11 * 32;
				_acceleration = 0;
				_velocity = 0;
				_dramatic_stop = false;
				_Hero->take_hit(_golem_1->_attack);
				_soundEngine->play2D("Resources/rpg_sound_pack/RPG_Sound_Pack/NPC/gutteral beast/mnstr3.wav", GL_FALSE);
				_golem_1_turn = false;
				_golem_2_turn = true;
			}
			_tiles[1]->setPosition(pos);
		}
	}
	else if (_golem_2_turn)
	{
		if (!_dramatic_stop)
		{
			_acceleration = -25;
			_velocity += _acceleration * dt;
			glm::vec3 pos = _tiles[2]->getPosition();
			pos.y += _velocity * dt;
			if (pos.y < 9 * 32)
			{
				pos.y = 9 * 32;
				_acceleration = 0;
				_velocity = 0;
				_dramatic_stop = true;
				_soundEngine->play2D("Resources/rpg_sound_pack/RPG_Sound_Pack/NPC/gutteral beast/mnstr3.wav", GL_FALSE);
			}
			_tiles[2]->setPosition(pos);
		}
		else
		{
			_acceleration = 25;
			_velocity += _acceleration * dt;
			glm::vec3 pos = _tiles[2]->getPosition();
			pos.y += _velocity * dt;
			if (pos.y > 11 * 32)
			{
				pos.y = 11 * 32;
				_acceleration = 0;
				_velocity = 0;
				_dramatic_stop = false;
				_Hero->take_hit(_golem_2->_attack);
				_soundEngine->play2D("Resources/rpg_sound_pack/RPG_Sound_Pack/NPC/gutteral beast/mnstr3.wav", GL_FALSE);
				_golem_2_turn = false;
				_hero_turn = true;
				_Hero->_defending = false;
			}
			_tiles[2]->setPosition(pos);
		}
	}
	if (_Hero->_current_health <= 0) gameStateManager.pushState(new ExitState(_soundEngine));
}

void TheGame::render(Renderer& renderer)
{
	renderer.useShader(ResourceManager::getShader("basic"));
	for(Tile* tile : _tiles)
	{
		tile->draw(renderer);
	}
	const Font* font = ResourceManager::getFont("Lato24");
	renderer.useShader(ResourceManager::getShader("text"));
	if(_active_option == 0)
	renderer.drawText("Attack", font, glm::vec3(32 * 20, 32 * 5, 0), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	else renderer.drawText("Attack", font, glm::vec3(32 * 20, 32 * 5, 0), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	if(_active_option == 1)
	renderer.drawText("Defend", font, glm::vec3(32 * 20, 32 * 4, 0), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	else renderer.drawText("Defend", font, glm::vec3(32 * 20, 32 * 4, 0), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	if (_active_option == 2)
		renderer.drawText("Golem 1", font, glm::vec3(32 * 20, 32 * 19, 0), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	else renderer.drawText("Golem 1", font, glm::vec3(32 * 20, 32 * 19, 0), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	if (_active_option == 3)
		renderer.drawText("Golem 2", font, glm::vec3(32 * 20, 32 * 18, 0), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	else renderer.drawText("Golem 2", font, glm::vec3(32 * 20, 32 * 18, 0), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	font = ResourceManager::getFont("Lato18");
	renderer.drawText("Golem 1 HP: " + _golem_1->hp_ratio(), font, glm::vec3(32 * 18, 32 * 15, 0), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	renderer.drawText("Golem 2 HP: " + _golem_2->hp_ratio(), font, glm::vec3(32 * 18, 32 * 13, 0), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	renderer.drawText("Hero HP: " + _Hero->hp_ratio(), font, glm::vec3(32 * 18, 32 * 10, 0), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
}

void TheGame::handleInput(const Window& window)
{
	if (!window.isKeyboardKeyPressed(GLFW_KEY_UP) && !window.isKeyboardKeyPressed(GLFW_KEY_DOWN) && !window.isKeyboardKeyPressed(GLFW_KEY_ENTER)) _key_pressed = false;
	if(window.isKeyboardKeyPressed(GLFW_KEY_UP) && !_key_pressed && _hero_turn)
	{
		_key_pressed = true;
		if (_active_option > 0 && !_action_chosen)
			_active_option--;
		else if (_active_option > 2 && _action_chosen)
			_active_option--;
	}
	else if(window.isKeyboardKeyPressed(GLFW_KEY_DOWN) && !_key_pressed && _hero_turn)
	{
		_key_pressed = true;
		if (_active_option < 1 && !_action_chosen)
			_active_option++;
		else if (_active_option < 3 && _action_chosen)
			_active_option++;
	}
	else if(window.isKeyboardKeyPressed(GLFW_KEY_ENTER) && !_key_pressed && _hero_turn)
	{
		_key_pressed = true;
		if(!_action_chosen)
		{
			_action_chosen = true;
			if (_active_option == 0)
			{
				_attack = true;
				_soundEngine->play2D("Resources/rpg_sound_pack/RPG_Sound_Pack/battle/sword_unsheathe.wav", GL_FALSE);
			}
			if (_active_option != 0)
			{
				_defend = true;
				_soundEngine->play2D("Resources/rpg_sound_pack/RPG_Sound_Pack/battle/spell.wav", GL_FALSE);
			}
				_active_option = 2;
		}

		else
		{
			if(_attack)
			{
				if (_active_option == 2)
					_target_enemy1 = true;
				else _target_enemy2 = true;
			}
			//_hero_turn = false;
			//_active_option = 5;
		}
	}
}
