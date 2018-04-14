#pragma once
#include <GL/glew.h>

class Buffer
{
private:
	GLuint _bufferID;
	GLuint _componentCount;
public:
	Buffer(GLfloat* data, GLsizei count, GLuint componentCount);
	void bind() const;
	void unbind() const;

	GLuint getComponentCount() const { return _componentCount; };
};