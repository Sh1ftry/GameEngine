#pragma once
#include <nlohmann/json.hpp>
#include "MapManager.h"
#include <fstream>

/**
* @brief Class responsible for properly parsing JSON 
*/

class JSONParser
{
	/**
	* @brief json that holds names of all Files that are map JSON's
	*/
	nlohmann::json _File_Names;
	/**
	* @brief name of a file that hold information about what files are to be parsed
	*/
	const std::string _info_file;

	/**
	* @brief Parses one map
	*/
	Map parse_JSON_to_map(const std::string &file_name)
	{
		std::vector<Layer> layers;
		std::vector<TileSetInfo> tile_infos;
		nlohmann::json map_json = load_json(file_name);
		layers.resize(map_json["layers"].size());
		tile_infos.resize(map_json["tilesets"].size());

		for(int i = 0; i < layers.size(); i++)
		{
			layers[i] = load_layer(map_json["layers"][i]);
		}

		for (int i = 0; i < layers.size(); i++)
		{
			layers[i] = load_layer(map_json["layers"][i]);
		}

		for(int i = 0; i < tile_infos.size(); i++)
		{
			tile_infos[i] = load_tile_set_info(map_json["tilesets"][i]);
		}
		return Map(tile_infos, layers);
	}

	/**
	* @brief loads map to JSON for further parsing, throws exception if file couldn't be open
	*/
	nlohmann::json load_json(const::std::string &file_name)
	{
		nlohmann::json map_json;
		std::ifstream map_info(file_name);
		if(map_info.is_open())
		{
			map_info >> map_json;
			map_info.close();
		}
		else throw std::invalid_argument("Couldn't open map file");
		return map_json;
	}

	/**
	* @brief parses one layer
	*/
	Layer load_layer(const nlohmann::json &map_json)
	{
		std::vector<int> tile_ids;
		std::string name = map_json["name"];
		tile_ids.resize(map_json["data"].size());
		for (int i = 0; i < tile_ids.size(); i++)
			tile_ids[i] = map_json["data"][i];
		return Layer(tile_ids, name);
	}

	/**
	* @brief parses one tile set
	*/
	TileSetInfo load_tile_set_info(const nlohmann::json &map_json)
	{
		int no_of_columns = map_json["columns"];
		int offset = map_json["firstgid"];
		std::string file_path = map_json["image"];
		std::string name = map_json["name"];
		int tile_count = map_json["tilecount"];
		return TileSetInfo(no_of_columns, offset, file_path, name, tile_count);
	}

public:
	JSONParser(const std::string &info_file) : _info_file(info_file) {}

	/**
	* @brief parses info_file JSON to File_Names, throws exception if file couldn't be open
	*/
	void read_info_file()
	{
		std::ifstream info_file(_info_file);
		if(info_file.is_open())
		{
			info_file >> _File_Names;
			info_file.close();
		}
		else throw std::invalid_argument("Couldn't open info_file");
	}

	MapManager* parse_JSON_to_map_manager()
	{
		std::vector<Map> map_list;
		map_list.resize(_File_Names["File_Names"].size());
		for(int i = 0; i < map_list.size(); i++)
		{
			map_list[i] = parse_JSON_to_map(_File_Names["File_Names"][i]);
		}
		return new MapManager(map_list);
	}
};
