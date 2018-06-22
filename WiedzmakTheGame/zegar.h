#pragma once
#include "MapObject.h"
#include <string>
#include <vector>
#include <time.h>
#include <chrono>

/**
* @brief class that represents 'zegar' object in the game
*/

class zegar : public MapObject
{
private:
	std::vector<std::string> _dialogue_lines;
	int _current_dialogue;
public:
	zegar()
	{
		_current_dialogue = 0;
		_dialogue_lines.push_back("*Zegar pokazuje nie tylko godzine, ale rowniez dzien i rok*");
		_dialogue_lines.push_back("Wojtek: A ten zepsuty zegar nadal zla date pokazuje");
		_dialogue_lines.push_back("Wojtek: Ze tez nikt go nie naprawil");
		_dialogue_lines.push_back(get_date());
	}
	std::string get_date() const
	{
		std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
		time_t t = std::chrono::system_clock::to_time_t(p);
		char str[26];
		ctime_s(str, sizeof str, &t);
		return str;
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
