#pragma once
#include <vector>

/**
* @brief hold all the information about layer parsed from JSON
*/

class Layer
{
private:
	std::vector<int> _tile_ids;
	std::string _name;
public:
	Layer(const std::vector<int>& is, const std::string& cs)
		: _tile_ids(is),
		  _name(cs)
	{
	}

	Layer() = default;

	std::vector<int> tile_ids() const
	{
		return _tile_ids;
	}

	void set_tile_id(const std::vector<int>& is)
	{
		_tile_ids = is;
	}

	std::string name() const
	{
		return _name;
	}

	void set_name(const std::string& cs)
	{
		_name = cs;
	}
};
