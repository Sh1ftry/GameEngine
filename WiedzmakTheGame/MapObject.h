#pragma once
#include <irrKlang/ik_ISoundEngine.h>

/**
* @brief Interface which represents every tile in a game, every square on a map is MapObject
*/

class MapObject
{
public:
	MapObject() = default;
	virtual bool is_passable() = 0;
	virtual bool interact() = 0;
	virtual bool on_pass(irrklang::ISoundEngine* soundEngine) = 0;
	virtual bool back()
	{
		return false;
	}
	virtual std::string description()
	{
		return "Hmph, nic ciekawego";
	}
	virtual void next_line() {}
	virtual ~MapObject() = default;
};
