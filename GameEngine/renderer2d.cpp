#include "vertex_data.h"
#include <GL/glew.h>
#include "renderer2d.h"

Renderer2D::Renderer2D()
	: _indexCount(0)
{
	glGenBuffers(1, &_buffer);
	glGenVertexArrays(1, &_vertexArray);

	glBindVertexArray(_vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, _buffer);
	
	glBufferData(GL_ARRAY_BUFFER, BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
	
	glEnableVertexAttribArray(POSITION_INDEX);
	glEnableVertexAttribArray(COLOR_INDEX);
	glVertexAttribPointer(POSITION_INDEX, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const GLvoid*)0);
	glVertexAttribPointer(COLOR_INDEX, 4, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const GLvoid*)(3 * sizeof(GLfloat)));
	
	glBindBuffer(GL_ARRAY_BUFFER, NULL);

	GLushort indices[MAX_INDICES];
	int offset = 0;
	for(int i = 0; i < MAX_INDICES; i+=6)
	{
		indices[i] = offset;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 2;
		indices[i + 3] = offset + 2;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset;
		
		offset += 4;
	}

	_indexBuffer = new IndexBuffer(indices, MAX_INDICES);
	glBindVertexArray(NULL);
}

void Renderer2D::begin()
{
	glBindBuffer(GL_ARRAY_BUFFER, _buffer);
	data = static_cast<VertexData*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
}

void Renderer2D::end()
{
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);
}

void Renderer2D::submit(const Renderable2D& renderable)
{

	const glm::vec3& position = renderable.getPosition();
	const glm::vec2& size = renderable.getSize();
	const glm::vec4& color = renderable.getColor();
	
	data->_position = glm::vec3(position.x, position.y, 0.f);
	data->_color = color;
	data++;

	data->_position = glm::vec3(position.x, position.y + size.y, 0.f);
	data->_color = color;
	data++;

	data->_position = glm::vec3(position.x + size.x, position.y + size.y, 0.f);
	data->_color = color;
	data++;

	data->_position = glm::vec3(position.x + size.x, position.y, 0.f);
	data->_color = color;
	data++;

	_indexCount += 6;
}

void Renderer2D::flush()
{
	glBindVertexArray(_vertexArray);
	_indexBuffer->bind();
	
	glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_SHORT, 0);
	
	_indexBuffer->unbind();
	glBindVertexArray(NULL);
	_indexCount = 0;
}
