#pragma once
#include "GameState.h"
#include "character.h"
#include "Character2.h"
#include "tile.h"
#include "MapManager.h"

class Window;

/**
* @brief class responsible for magaing the exploration part of the game
*/

class MapState : public GameState
{
private:
	std::vector<Tile*> _tiles;
	irrklang::ISoundEngine* _soundEngine;
	Tile* _dialogue_background;
	MapManager* _map_manager;
	Character2* _character2;
	int _current_map_id;
	std::vector<std::string> _music;
public:
	MapState(irrklang::ISoundEngine* soundEngine);
	~MapState();
	void change_map();
	void move_character() const;
	void update(GameStateManager& gameStateManager, float dt) override;
	void render(Renderer& renderer) override;
	void handleInput(const Window& window) override;
};

