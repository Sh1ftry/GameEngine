#pragma once
#include "MapObject.h"
#include <string>
#include <vector>

/**
* @brief class represents a 'Babcia' character in a game
*/

class Babcia : public MapObject
{
private:
	std::vector<std::string> _dialogue_lines;
	int _current_dialogue;
public:
	Babcia()
	{
		_current_dialogue = 0;
		_dialogue_lines.push_back("Ciotka: Wszystkiego najlepszego Wojtku!");
		_dialogue_lines.push_back("Ciotka: Ale zes wydoroslal...");
		_dialogue_lines.push_back("Ciotka: Chlip chlip");
		_dialogue_lines.push_back("Ciotka: Jestes bardzo podobny do swojej Matki, wiesz o tym?");
		_dialogue_lines.push_back("Wojtek: Dzieki ciociu, doceniam");
		_dialogue_lines.push_back("Ciotka: Nie ma za co skarbie, jakbys czegos potrzebowal, to bede tu do wieczora");
		_dialogue_lines.push_back("Ciotka: Do wieczora!");
	}
	bool is_passable() override
	{
		return false;
	}
	bool interact() override
	{
		return true;
	}
	std::string description() override
	{
		std::string desc = _dialogue_lines[_current_dialogue];
		return desc;
	}
	void next_line() override
	{
		if (_current_dialogue < _dialogue_lines.size() - 1)
			_current_dialogue++;
	}
	bool on_pass(irrklang::ISoundEngine* soundEngine) override
	{
		return false;
	}
};