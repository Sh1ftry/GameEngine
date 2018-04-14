#include "vertexarray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &_vertexID);
}

VertexArray::~VertexArray()
{
	for(Buffer* buffer : _buffers)
	{
		delete buffer;
	}
}

void VertexArray::addBuffer(Buffer * buffer, GLuint index)
{
	bind();
	buffer->bind();
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);
	buffer->unbind();
	unbind();
}

void VertexArray::bind()
{
	glBindVertexArray(_vertexID);
}

void VertexArray::unbind()
{
	glBindVertexArray(0);
}
