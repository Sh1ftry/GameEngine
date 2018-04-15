#include "simple_renderer2d.h"
#include <glm/gtc/matrix_transform.hpp>

void SimpleRenderer2D::submit(const Renderable2D& renderable)
{
	_renderQueue.push_back(&renderable);
}

void SimpleRenderer2D::flush()
{
	while(!_renderQueue.empty())
	{
		const Renderable2D* renderable = _renderQueue.front();
		_renderQueue.pop_front();
		renderable->getVAO()->bind();
		renderable->getIBO()->bind();
		glm::mat4 translation(1.f);
		translation = glm::translate(translation, renderable->position());
		renderable->getShader().setUniformMat4("model", translation);
		glDrawElements(GL_TRIANGLES, renderable->getIBO()->getCount(), GL_UNSIGNED_SHORT, 0);
		renderable->getIBO()->unbind();
		renderable->getVAO()->unbind();

	}
}
