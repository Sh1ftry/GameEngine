#pragma once
#include "MapObject.h"

/**
* @brief class represents MapObject that transits player to another map when stepped on
*/

class TransitionTile : public MapObject
{
public:
	bool _back;
	TransitionTile() = default;
	TransitionTile(bool back) : _back(back) {}
	bool is_passable() override
	{
		return true;
	}
	bool on_pass(irrklang::ISoundEngine* soundEngine) override
	{
		soundEngine->play2D("Resources/door.wav", GL_FALSE);
		return true;
	}

	bool back() override
	{
		return _back;
	}

	bool interact() override
	{
		return false;
	}
};