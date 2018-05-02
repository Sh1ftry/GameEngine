#pragma once
#include <GL/glew.h>
#include <glm/detail/type_vec2.hpp>

class Texture
{
	GLuint _id;
	glm::vec2 _size;
	glm::vec2 _gridSize;
	glm::vec2 _frameSize;
public:
	Texture(GLuint texture, unsigned int height, unsigned int width, unsigned int rows, unsigned int cols) 
	: _id(texture), _size(glm::vec2(width, height)), _gridSize(cols, rows), _frameSize(_size/_gridSize) {};
	
	void use(unsigned int textureNumber) const
	{
		glActiveTexture(GL_TEXTURE0 + textureNumber);
		glBindTexture(GL_TEXTURE_2D, _id);
	}

	GLuint getID() const
	{
		return _id;
	}

	const glm::vec2& getSize() const
	{
		return _size;
	}

	const glm::vec2& getGridSize() const
	{
		return _gridSize;
	}

	const glm::vec2& getFrameSize() const
	{
		return _frameSize;
	}
};
