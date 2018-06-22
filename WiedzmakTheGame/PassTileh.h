#pragma once
#include "MapObject.h"
#include <irrKlang/ik_ISoundEngine.h>

/**
* @brief class represents the most simple MapObject in a game that's just a passable floor tile
*/

class PassTile : public MapObject
{
public:
	PassTile() = default;
	bool is_passable() override
	{
		return true;
	}
	bool interact() override
	{
		return false;
	}
	bool on_pass(irrklang::ISoundEngine* soundEngine) override
	{
		//soundEngine->play2D("Resources/Fantozzi-SandL2.flac", GL_FALSE);
		return false;
	}

};
