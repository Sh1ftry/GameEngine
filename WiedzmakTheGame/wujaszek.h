#pragma once
#include "MapObject.h"
#include <string>
#include <vector>

/**
* @brief class represents 'wujaszek' NPC in the game
*/

class wujaszek : public MapObject
{
private:
	std::vector<std::string> _dialogue_lines;
	int _current_dialogue;
public:
	wujaszek()
	{
		_current_dialogue = 0;
		_dialogue_lines.push_back("Wujek: Uwazaj wojtku!");
		_dialogue_lines.push_back("Wojtek: ???");
		_dialogue_lines.push_back("Wujek: KTOS ZATRUL STUDNIE");
		_dialogue_lines.push_back("Wujek: ...");
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