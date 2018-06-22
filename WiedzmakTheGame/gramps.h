#pragma once
#include "MapObject.h"
#include <string>
#include <vector>

class gramps : public MapObject
{
private:
	std::vector<std::string> _dialogue_lines;
	int _current_dialogue;
public:
	gramps()
	{
		_current_dialogue = 0;
		_dialogue_lines.push_back("Zbigniew: Co Wojtku, jestes gotowy na swoj wielki debiut?");
		_dialogue_lines.push_back("Wojtek: Nie wierze ze nadal sie ludzisz ze zostane piekarzem");
		_dialogue_lines.push_back("Wojtek: nie wiem jak ty mozesz to zniesc ale ja im nigdy nie wybacze");
		_dialogue_lines.push_back("Zbigniew: Ja tylko chce zebys nie skonczyl jak twoja Matka");
		_dialogue_lines.push_back("Wojtek: Taa, ona nie zgodzila by sie na takie zycie!");
		_dialogue_lines.push_back("Zbigniew: ...");
		_dialogue_lines.push_back("Wojtek: ...!");
		_dialogue_lines.push_back("Wojtek: .....");
		_dialogue_lines.push_back("Wojtek: Ja... potrzebuje ...");
		_dialogue_lines.push_back("Wojtek: ...");
		_dialogue_lines.push_back("Wojtek: Ide sie przewietrzyc, chcesz czegos?");
		_dialogue_lines.push_back("Zbigniew: Nie otrzymalem jeszcze odpowiedzi od Justyny");
		_dialogue_lines.push_back("Zbigniew: Moglbys do niej pojsc i zobaczyc czy przyjdzie?");
		_dialogue_lines.push_back("Zbigniew: Spokojnie trafisz, musisz tylko kierowac sie na wschod");
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
