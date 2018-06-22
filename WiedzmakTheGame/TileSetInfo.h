#pragma once
#include <string>

/**
* @brief class holds information parsed from JSON about tileset in a map
*/

class TileSetInfo
{
	int _no_of_columns;
	int _offset;
	std::string _file_path;
	std::string _name;
	int _tile_count;
public:
	TileSetInfo(int no_of_columns, int offset, const std::string& cs, const std::string& cs1, int tile_count)
		: _no_of_columns(no_of_columns),
		  _offset(offset),
		  _file_path(cs),
		  _name(cs1),
		  _tile_count(tile_count)
	{
	}

	TileSetInfo() = default;

	int no_of_columns() const
	{
		return _no_of_columns;
	}

	void set_no_of_columns(int no_of_columns)
	{
		_no_of_columns = no_of_columns;
	}

	int offset() const
	{
		return _offset;
	}

	void set_offset(int offset)
	{
		_offset = offset;
	}

	std::string file_path() const
	{
		return _file_path;
	}

	void set_file_path(const std::string& cs)
	{
		_file_path = cs;
	}

	std::string name() const
	{
		return _name;
	}

	void set_name(const std::string& cs)
	{
		_name = cs;
	}

	int tile_count() const
	{
		return _tile_count;
	}

	void set_tile_count(int tile_count)
	{
		_tile_count = tile_count;
	}
};

