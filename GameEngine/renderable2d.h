#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "buffer.h"
#include "indexbuffer.h"
#include "vertexarray.h"
#include "shader.h"

/**
 * @brief	Class representing renderable 2d object that has
 *			position, size and color. It can be rendered using
 *			SimpleRenderer2D
 * @see		SimpleRenderer2D
 */
class Renderable2D
{
protected:
	glm::vec2 _size;
	glm::vec3 _position;
	glm::vec4 _color;

	IndexBuffer* _indexBuffer;
	VertexArray* _vertexArray;
	Shader& _shader;
public:
	/**
	 * @brief	Creates index buffer and vertex array used for rendering this object
	 * @param	position	position on the screen
	 * @param	size		size of object
	 * @param	color		color of the object
	 * @param	shader		which shader whould be used during rendering
	 */
	Renderable2D(glm::vec3 position, glm::vec2 size, glm::vec4 color, Shader& shader)
		: _size(size), _position(position), _color(color), _shader(shader)
	{

		GLfloat vertices[] =
		{
			0, 0, 0,
			0, _size.y, 0,
			_size.x, _size.y, 0,
			_size.x, 0, 0
		};

		GLfloat colors[] =
		{
			_color.x, _color.y, _color.z, _color.w,
			_color.x, _color.y, _color.z, _color.w,
			_color.x, _color.y, _color.z, _color.w,
			_color.x, _color.y, _color.z, _color.w,
		};

		_vertexArray = new VertexArray();
		_vertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
		_vertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);
		
		GLushort indices[] = { 0, 1, 2, 2, 3, 0 };
		_indexBuffer = new IndexBuffer(indices, 6);
	}

	virtual ~Renderable2D()
	{
		delete _indexBuffer;
		delete _vertexArray;
	}

	/**
	 * @return vec2 with size of the object
	 */
	const glm::vec2& size() const
	{
		return _size;
	}

	/**
	 * @return vec3 with position of the object
	 */
	const glm::vec3& position() const
	{
		return _position;
	}

	/**
	 * @return vec4 with color of the object
	 */
	const glm::vec4& color() const
	{
		return _color;
	}

	/**
	 * @return pointer to IndexBuffer
	 */
	const IndexBuffer* getIBO() const
	{
		return _indexBuffer;
	}

	/**
	 * @return pointer to VertexArray
	 */
	const VertexArray* getVAO() const
	{
		return _vertexArray;
	}

	/**
	 * @return refrence to shader
	 */
	Shader& getShader() const
	{
		return _shader;
	}
};