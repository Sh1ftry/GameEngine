#pragma once
#include "MapObject.h"
#include <irrKlang/ik_ISoundEngine.h>

/**
* @brief class represent the most simple MapObject in a game that's just impassable tile
*/

class SolidTile : public MapObject
{
public:
	SolidTile() = default;
	bool is_passable() override
	{
		return false;
	}
	bool interact() override
	{
		return true;
	}
	bool on_pass(irrklang::ISoundEngine* soundEngine) override
	{
		return false;
	}
};
