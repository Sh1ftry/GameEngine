#pragma once
#include <deque>
#include "renderer2d.h"

/**
 * @brief	Class implementing Renderer2D representing 
 *			a simple, non-optimized rendered capable of
 *			rendering Renderable2D objects
 * @see		Renderable2D
 * @see		Renderer2D
 */
class SimpleRenderer2D : public Renderer2D
{
private:
	//render queue
	std::deque<const Renderable2D*> _renderQueue;
public:
	/**
	 * @brief	Adds renderable object to render queue
	 * @param	renderable	Renderable2D object 
	 */
	void submit(const Renderable2D& renderable) override;
	/**
	 * @brief Renders all objects stored in render queue
	 */
	void flush() override;
};