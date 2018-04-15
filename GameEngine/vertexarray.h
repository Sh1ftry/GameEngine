#pragma once

#include <vector>
#include "GL/glew.h"
#include "buffer.h"

class VertexArray
{
private:
	GLuint _vertexID;
	std::vector<Buffer*> _buffers;
public:
	VertexArray();
	~VertexArray();

	void addBuffer(Buffer* buffer, GLuint index);
	void bind() const;
	void unbind() const;
};