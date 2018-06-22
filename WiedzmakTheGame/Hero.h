#pragma once
class Hero
{
public:
	int _current_health;
	int _defense_reduction;
	int _attack;
	int _max_health;
	bool _dead;
	bool _defending;

	Hero()
	{
		_defense_reduction = 99;
		_max_health = 500;
		_current_health = _max_health;
		_attack = 100;
		_dead = false;
		_defending = false;
	}

	std::string hp_ratio() const
	{
		return std::to_string(_current_health) + "/" + std::to_string(_max_health);
	}

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
