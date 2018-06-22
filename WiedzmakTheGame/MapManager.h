#pragma once
#include "Map.h"
#include <nlohmann/json.hpp>
#include "MapObject.h"
#include "SolidTile.h"
#include "PassTileh.h"
#include "TransitionTile.h"
#include "gramps.h"
#include "Babcia.h"
#include "wujaszek.h"
#include "zegar.h"

/**
 * @brief Class responsible for loading and managing maps
 */


class MapManager
{
	std::vector<Map> _map_list;
	int _current_map_number;
	std::vector<std::unique_ptr<MapObject>> _coll_map;
	int _x;
	int _y;

	/**
	* @brief adds tiles that transit character to another map 
	*/
	void add_Transistion()
	{
		switch(_current_map_number)
		{
		case 0:
			_coll_map[11 + 5 * 25] = std::make_unique<TransitionTile>(TransitionTile(false));
			_coll_map[12 + 5 * 25] = std::make_unique<TransitionTile>(TransitionTile(false));
			_coll_map[13 + 5 * 25] = std::make_unique<TransitionTile>(TransitionTile(false));
			_coll_map[9 + 15 * 25] = std::make_unique<gramps>(gramps());
			break;
		case 1:
			_coll_map[19 + 4 * 25] = std::make_unique<TransitionTile>(TransitionTile(true));
			_coll_map[24 + 10 * 25] = std::make_unique<TransitionTile>(TransitionTile(false));
			_coll_map[24 + 11 * 25] = std::make_unique<TransitionTile>(TransitionTile(false));
			_coll_map[24 + 12 * 25] = std::make_unique<TransitionTile>(TransitionTile(false));
			_coll_map[8 + 3 * 25] = std::make_unique<Babcia>(Babcia());
			_coll_map[16 + 16 * 25] = std::make_unique<wujaszek>(wujaszek());
			/*
			change_coll(std::make_unique<TransitionTile>(TransitionTile(true)), 19, 4);
			change_coll(std::make_unique<TransitionTile>(TransitionTile(false)), 24, 10);
			change_coll(std::make_unique<TransitionTile>(TransitionTile(false)), 24, 11);
			change_coll(std::make_unique<TransitionTile>(TransitionTile(false)), 24, 12);
			change_coll(std::make_unique<Babcia>(Babcia()), 8, 3);
			change_coll(std::make_unique<wujaszek>(wujaszek()), 16, 16);
			*/
			break;
		case 2:
			_coll_map[0 + 10 * 25] = std::make_unique<TransitionTile>(TransitionTile(true));
			_coll_map[0 + 11 * 25] = std::make_unique<TransitionTile>(TransitionTile(true));
			_coll_map[0 + 12 * 25] = std::make_unique<TransitionTile>(TransitionTile(true));
			_coll_map[24 + 10 * 25] = std::make_unique<TransitionTile>(TransitionTile(false));
			_coll_map[24 + 11 * 25] = std::make_unique<TransitionTile>(TransitionTile(false));
			_coll_map[24 + 12 * 25] = std::make_unique<TransitionTile>(TransitionTile(false));
			_coll_map[14 + 13 * 25] = std::make_unique<zegar>(zegar());
			_coll_map[15 + 13 * 25] = std::make_unique<zegar>(zegar());
			/*
			change_coll(std::make_unique<TransitionTile>(TransitionTile(true)), 0, 10);
			change_coll(std::make_unique<TransitionTile>(TransitionTile(true)), 0, 11);
			change_coll(std::make_unique<TransitionTile>(TransitionTile(true)), 0, 12);
			change_coll(std::make_unique<TransitionTile>(TransitionTile(false)), 24, 10);
			change_coll(std::make_unique<TransitionTile>(TransitionTile(false)), 24, 11);
			change_coll(std::make_unique<TransitionTile>(TransitionTile(false)), 24, 10);
			change_coll(std::make_unique<zegar>(zegar()), 14, 13);
			change_coll(std::make_unique<zegar>(zegar()), 15, 13);
			*/
			break;
		default:
			break;
		}
	}

public:
	MapManager(const std::vector<Map> &map_list) : _map_list(map_list)
	{
		_current_map_number = 0;
		fill_coll_map();
	}

	MapManager() = default;

	/**
	* @brief when character transits to new map, this function loads collisions
	*/
	void fill_coll_map()
	{
		std::vector<int> id = get_layer_by_name("Coll").tile_ids();
		_coll_map.clear();
		_coll_map.resize(id.size());
		int i = 0;
		for(int data : id)
		{
			int x = i % 25;
			int y = (i - x) / 25;
			int tab = (19 - y) * 25 + x;
			if (data != 0)
			{
				_coll_map[tab] = std::make_unique<SolidTile>(SolidTile());
			}
			else
			{
				_coll_map[tab] = std::make_unique<PassTile>(PassTile());
			}
			i++;
		}
		add_Transistion();
	}

	/**
	* @brief Simple MapObject getter
	* @param x object's x position
	* @param y object's y position
	*/
	MapObject* operator()(unsigned int x, unsigned int y)
	{
		_x = x;
		_y = y;
		int i = x + y * 25;
		if(i < _coll_map.size())
			return _coll_map[i].get();
		return nullptr;
	}
	/**
	* @brief function return filename of tileset
	* @param i which tileset within map 
	*/
	std::string get_tile_set_name(int i)
	{
		return _map_list[_current_map_number].tile_set()[i].file_path();
	}
	/**
	* @brief function return where in a tileset is specified tile
	* @param coordinates coordinates of a tile in JSON
	* @param layer in which layer the tile is 
	*/
	int get_tile_number_within_tile_set(int coordinates, int layer)
	{
		int number_within_tile_set = 0;
		if(layer < _map_list[_current_map_number].layers().size() && coordinates < _map_list[_current_map_number].layers()[layer].tile_ids().size())
		{
			std::vector<int> bounds;
			for(int i = 0; i < _map_list[_current_map_number].tile_set().size(); i++)
				bounds.push_back(_map_list[_current_map_number].tile_set()[i].offset());
			int tile_id = _map_list[_current_map_number].layers()[layer].tile_ids()[coordinates];

			int bound;
			for(int i = bounds.size()-1; i >= 0; i--)
			{
				bound = bounds[i];
				if (tile_id > bound) number_within_tile_set = tile_id - bound;
			}
		}
		return number_within_tile_set;
	}

	/**
	* @brief returns both order number of a tile in tileset and tileset name
	* @param coordinates coordinates of a tile in JSON
	* @param layer in which layer the tile is
	*/
	std::pair<int,int> get_tile_number_within_tile_set_and_tile_no(int coordinates, int layer)
	{
		int number_within_tile_set = 0;
		std::pair<int, int> pair;
		pair.first = 0;
		if (layer < _map_list[_current_map_number].layers().size() && coordinates < _map_list[_current_map_number].layers()[layer].tile_ids().size())
		{
			std::vector<int> bounds;
			for (int i = 0; i < _map_list[_current_map_number].tile_set().size(); i++)
				bounds.push_back(_map_list[_current_map_number].tile_set()[i].offset());
			int tile_id = _map_list[_current_map_number].layers()[layer].tile_ids()[coordinates];

			int bound;
			for (int i = bounds.size() - 1; i >= 0; i--)
			{
				bound = bounds[i];
				if (tile_id > bound)
				{
					pair.first = tile_id - bound;
					pair.second = i;
				}
			}
		}
		return pair;
	}

	/**
	* @brief return layer with specified name
	* @param name name of a layer
	*/
	Layer get_layer_by_name(const std::string &name)
	{
		Layer named_layer;
		for(Layer layer : _map_list[_current_map_number].layers())
		{
			if (layer.name() == name)
			{
				named_layer = layer;
				break;
			}
		}
		return named_layer;
	}

	/**
	* @brief loads next map
	*/
	void load_next_map()
	{
		if (!(_current_map_number+1 >= _map_list.size()))
		{
			_current_map_number++;
			fill_coll_map();
		}
	}

	/**
	* @brief loads prev map
	*/
	void load_prev_map()
	{
		if(_current_map_number > 0)
		{
			_current_map_number--;
			fill_coll_map();
		}
	}
	/**
	* @brief current map getter
	*/
	Map map() const
	{
		return _map_list[_current_map_number];
	}
	/**
	* @brief current map number getter
	*/
	int map_no() const
	{
		return _current_map_number;
	}
	/**
	* @brief return x position of last accesed MapObject
	*/
	int x() const
	{
		return _x;
	}
	/**
	* @brief return y position of last accesed MapObject
	*/
	int y() const
	{
		return _y;
	}

	
	~MapManager()
	{
		/*
		for(MapObject* map_object : _coll_map)
		{
			delete map_object;
		}
		*/

		/*
		for(auto i = _coll_map.begin(); i!=_coll_map.end(); ++i)
		{
			delete i->release();
		}
		*/
	}
	
};
