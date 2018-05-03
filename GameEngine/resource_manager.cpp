#include "resource_manager.h"
#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>

std::map<std::string, Texture*> ResourceManager::_textures;

void ResourceManager::loadTexture(const std::string& path, const std::string& name, unsigned int rows, unsigned int cols)
{
	stbi_set_flip_vertically_on_load(true);
	int width, height, channels;
	unsigned char* image = stbi_load(path.c_str(), &width, &height, &channels, 0);

	if(image)
	{
		GLuint texture;
		glGenBuffers(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);

		_textures[name] = new Texture(texture, height, width, rows, cols);

		stbi_image_free(image);
	}
	else
	{
		throw std::invalid_argument("File " + path + " does not exist!");
	}
}

const Texture* ResourceManager::getTexture(const std::string& name)
{
	return _textures.at(name);
}

ResourceManager::~ResourceManager()
{
	for(std::pair<std::string, Texture*> element: _textures)
	{
		delete element.second;
	}
}
