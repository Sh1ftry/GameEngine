#pragma once
#include <GL/glew.h>

class Texture
{
	GLuint _texture;
	unsigned int _height;
	unsigned int _widht;
	unsigned int _rows;
	unsigned int _cols;
public:
	Texture(GLuint texture, unsigned int height, unsigned int width, unsigned int rows, unsigned int cols) 
	: _texture(texture), _height(height), _widht(width), _rows(rows), _cols(cols) {};
	
	void use() const
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _texture);
	}

	GLuint getTextureID() const
	{
		return _texture;
	}


	unsigned getHeight() const
	{
		return _height;
	}

	unsigned getWidht() const
	{
		return _widht;
	}

	unsigned getRows() const
	{
		return _rows;
	}

	unsigned getCols() const
	{
		return _cols;
	}
};
