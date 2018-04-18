#pragma once
#include "indexbuffer.h"
#include "vertex_data.h"
#include "renderable2d.h"
#include "vertex_data.h"

class Renderer2D
{
private:

	static const int VERTEX_SIZE = sizeof(VertexData);
	static const int SPRITE_SIZE = 4 * VERTEX_SIZE;
	static const int MAX_SPRITES = 10000;
	static const int BUFFER_SIZE = SPRITE_SIZE * MAX_SPRITES;
	static const int MAX_INDICES = 6 * MAX_SPRITES;

	static const char POSITION_INDEX = 0;
	static const char COLOR_INDEX = 1;

	GLuint _vertexArray;
	GLuint _buffer;
	IndexBuffer* _indexBuffer;
	GLushort _indexCount;
	VertexData* data;
public:
	Renderer2D();
	~Renderer2D() = default;

	void begin();
	void end();
	void submit(const Renderable2D& renderable);
	void flush();
};