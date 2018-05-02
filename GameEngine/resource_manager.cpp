#include "resource_manager.h"
#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

std::map<std::string, Texture*> ResourceManager::textures;

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
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);

		textures[name] = new Texture(texture, height, width, rows, cols);

		stbi_image_free(image);
	}
}

const Texture & ResourceManager::getTexture(std::string name)
{
	return *textures.at(name);
}
