#pragma once

#include <string>
#include <map>
#include "../Graphics/texture.h"
#include "font.h"
#include "../Graphics/shader.h"

class ResourceManager
{
private:
	static std::map<std::string, Texture*> _textures;
	static std::map<std::string, Font*> _fonts;
	static std::map<std::string, Shader*> _shaders;

public:
	static void loadTexture(const std::string& path, const std::string& name, unsigned int rows, unsigned int cols);
	static const Texture* getTexture(const std::string& name);
	static void loadFont(const std::string& path, const std::string& name, unsigned int size);
	static const Font* getFont(const std::string& name);
	static void loadShaders(const std::string & vertexPath, const std::string & fragmentPath, const std::string & name);
	static const Shader* getShader(const std::string& name);
	~ResourceManager();
};
