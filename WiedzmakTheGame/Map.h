#pragma once
#include "Layer.h"
#include "TileSetInfo.h"

/**
* @brief Every single map is a vector of layers and tileSetInfos
*/

class Map
{
	std::vector<TileSetInfo> _tile_set;
	std::vector<Layer> _layers;
public:
	Map(const std::vector<TileSetInfo>& tile_set_infos, const std::vector<Layer>& layers)
		: _tile_set(tile_set_infos),
		  _layers(layers)
	{
	}

	Map() = default;

	std::vector<TileSetInfo> tile_set() const
	{
		return _tile_set;
	}

	void set_tile_set(const std::vector<TileSetInfo>& tile_set_infos)
	{
		_tile_set = tile_set_infos;
	}

	std::vector<Layer> layers() const
	{
		return _layers;
	}

	void set_layers(const std::vector<Layer>& layers)
	{
		_layers = layers;
	}
};
