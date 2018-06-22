#include "MapState.h"
#include "JSONParser.h"
#include "TransitionTile.h"


MapState::MapState(irrklang::ISoundEngine* soundEngine) : _soundEngine(soundEngine)
{
	_current_map_id = 0;
	JSONParser parser("Resources/file_names.json");
	parser.read_info_file();
	_map_manager = parser.parse_JSON_to_map_manager();
	//_map_manager = new MapManager();

	_dialogue_background = new Tile(glm::vec3(0, 0, -0.9f), glm::vec2(800, 96), ResourceManager::getTexture("dialogue"));

	std::string cs0 = "Resources/music/Adventures_of_small_brave _The_Mnk.mp3";
	std::string cs1 = "Resources/music/Passing_the_Torch.mp3";
	std::string cs2 = "Resources/music/Forest_Ambience.mp3";
	std::string cs3 = "Resources/music/Forest_Ambience.mp3";

	_music.push_back(cs0);
	_music.push_back(cs1);
	_music.push_back(cs2);
	_music.push_back(cs3);

	_soundEngine->stopAllSounds();
	_soundEngine->play2D(_music[0].c_str() , GL_TRUE);

	// = new Character(100, 80, 100, 157, _soundEngine);
	_character2 = new Character2(12*32, 12*32, 32, 36, _map_manager, _soundEngine);
	//_tiles.push_back(new Tile(glm::vec3(0, 0, -0.9f), glm::vec2(800, 600), ResourceManager::getTexture("house")));
	_tiles.push_back(new Tile(glm::vec3(0, 0, -0.9f), glm::vec2(800, 640), ResourceManager::getTexture("house_0")));
	_tiles.push_back(new Tile(glm::vec3(0, 0, -0.9f), glm::vec2(800, 640), ResourceManager::getTexture("house_1")));

	_tiles.push_back(new Tile(glm::vec3(0, 0, -0.9f), glm::vec2(800, 640), ResourceManager::getTexture("outside_0")));
	_tiles.push_back(new Tile(glm::vec3(0, 0, -0.9f), glm::vec2(800, 640), ResourceManager::getTexture("outside_1")));

	_tiles.push_back(new Tile(glm::vec3(0, 0, -0.9f), glm::vec2(800, 640), ResourceManager::getTexture("forest_0")));
	_tiles.push_back(new Tile(glm::vec3(0, 0, -0.9f), glm::vec2(800, 640), ResourceManager::getTexture("forest_1")));

	_tiles.push_back(new Tile(glm::vec3(0, 0, -0.9f), glm::vec2(800, 640), ResourceManager::getTexture("prelude_0")));
	_tiles.push_back(new Tile(glm::vec3(0, 0, -0.9f), glm::vec2(800, 640), ResourceManager::getTexture("prelude_1")));

}

void MapState::change_map()
{
	if (!_character2->back())
	{
		_current_map_id++;
		_soundEngine->stopAllSounds();
		_soundEngine->play2D(_music[_current_map_id].c_str(), GL_TRUE);
		move_character();
		//_map_manager.load_next_map();
	}
	else
	{
		_current_map_id--;
		_soundEngine->stopAllSounds();
		_soundEngine->play2D(_music[_current_map_id].c_str(), GL_TRUE);
		move_character();
	}
}

void MapState::move_character() const
{
	switch(_current_map_id)
	{
	case 0:
		_character2->set_transition(12, 5);
		break;
	case 1:
		if (_character2->back())
		_character2->set_transition(24, 12);
		else
		_character2->set_transition(19, 3);
		break;
	case 2:
		_character2->set_transition(0, 11);
		break;
	case 3:
		_character2->set_transition(0, 11);
		break;
	default:
		break;
	}
}


MapState::~MapState()
{
	//delete _character;
	delete _character2;
	/*
	for(Tile* tile : _tiles)
	{
		delete tile;
	}
	*/
	for(std::vector<Tile*>::iterator i = _tiles.begin(); i != _tiles.end(); ++i)
	{
		delete *i;
	}
	delete _map_manager;
	delete _dialogue_background;
}

void MapState::update(GameStateManager& gameStateManager, float dt)
{
	//_character->update(dt);
	_character2->update(dt);
	if (_character2->transition())
		change_map();
	if (_character2->theGame())
		gameStateManager.pushState(new TheGame(_soundEngine));
}

void MapState::render(Renderer& renderer)
{
	renderer.useShader(ResourceManager::getShader("basic"));
	/*
	for (Tile* tile : _tiles)
	{
		tile->draw(renderer);
	}
	*/
	_tiles[_current_map_id*2]->draw(renderer);
	//_character->draw(renderer);
	_character2->draw(renderer);
	_tiles[_current_map_id * 2 + 1]->draw(renderer);
	if (_character2->dialogue())
	{
		_dialogue_background->draw(renderer);
		const Font* font = ResourceManager::getFont("Lato24");
		renderer.useShader(ResourceManager::getShader("text"));
		const std::string dialogue = (*_map_manager)((*_map_manager).x(), (*_map_manager).y())->description();
		renderer.drawText(dialogue, font, glm::vec3(32, 48, 0), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	}
	//_tiles[2]->draw(renderer);
}

void MapState::handleInput(const Window& window)
{
	_character2->handleInput(window);
	//_character->handleInput(window);
}
