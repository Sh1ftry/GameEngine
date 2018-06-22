#pragma once
#include "GameState.h"
#include "tile.h"
#include "MapManager.h"
#include <vector>
#include <irrKlang/ik_ISoundEngine.h>
#include "Golem.h"
#include "Hero.h"

class Window;

/**
* @brief game state responsible of turn-based fighting of the game
*/

class TheGame : public GameState
{
private:
	std::vector<Tile*> _tiles;
	irrklang::ISoundEngine* _soundEngine;
	int _active_option;
	bool _attack;
	bool _defend;
	bool _action_chosen;
	bool _target_enemy1;
	bool _target_enemy2;
	bool _golem_1_turn;
	bool _golem_2_turn;
	bool _hero_animation;
	bool _hero_turn;
	bool _golem_1_animation;
	bool _golem_2_animation;
	bool _key_pressed;
	bool _dramatic_stop;
	float _time;

	float _velocity;
	int _acceleration;

	Golem* _golem_1;
	Golem* _golem_2;

	Hero* _Hero;
public:
	TheGame(irrklang::ISoundEngine* soundEngine);
	~TheGame();
	void update(GameStateManager& gameStateManager, float dt) override;
	void render(Renderer& renderer) override;
	void handleInput(const Window& window) override;
};

