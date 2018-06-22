#pragma once

/**
* @brief class represents the only enemy in the game - the golem
*/

class Golem
{
public:
	int _current_health;
	int _defense_reduction;
	int _attack;
	int _max_health;

	bool _previous_attacked;
	bool _previous_previous_attacked;

	bool _defending;
	bool _dead;

	Golem()
	{
		_defense_reduction = 100;
		_max_health = 500;
		_current_health = _max_health;
		_attack = 100;
		_defending = false;
		_dead = false;

		_previous_attacked = false;
		_previous_previous_attacked = false;
	}

	/**
	* @brief return golem's health in xxx/xxx string literal
	*/
	std::string hp_ratio() const
	{
		return std::to_string(_current_health) + "/" + std::to_string(_max_health);
	}

	/**
	* @brief calculating how much damage golem takes
	* @param attack attack value of the attacker
	*/
	void take_hit(int attack)
	{
		if (_defending)
			_current_health -= attack - _defense_reduction;
		else
			_current_health -= attack;
		if (_current_health < 0)
			_dead = true;
	}
};
