#pragma once
#include <GL/glew.h>

class IndexBuffer
{
private:
	GLuint _bufferID;
	GLuint _count;
public:
	IndexBuffer(GLushort* data, GLsizei count);
	void bind() const;
	void unbind() const;
	
	GLuint getCount() const { return _count; };
};