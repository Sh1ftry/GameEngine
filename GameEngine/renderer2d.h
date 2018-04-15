#pragma once
#include "renderable2d.h"

/**
 * @brief	Pure virtual class representing a renderer
 *			that can render Renderable2D objects
 * @see		Renderable2D
 */
class Renderer2D
{
protected:
	virtual void submit(const Renderable2D& renderable) = 0;
	virtual void flush() = 0;
	virtual ~Renderer2D();
}; 