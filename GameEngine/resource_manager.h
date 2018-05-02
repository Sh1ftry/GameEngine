#pragma once

#include <string>
#include <map>
#include "texture.h"

class ResourceManager
{
private:
	static std::map<std::string, Texture*> textures;
public:
	static void loadTexture(const std::string& path, const std::string& name, unsigned int rows, unsigned int cols);
	static const Texture& getTexture(std::string name);
};
