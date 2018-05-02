#include "animation.h"

Animation::Animation(const Texture* texture, const glm::vec2& from, const glm::vec2& to, float animationTime)
	: _texture(texture), _from(from), _to(to), _currentFrame(_from), _timeSinceLastAnimationFrame(0.0f)
{
	const unsigned int textureCols =_texture->getGridSize().x;
	int full = (_to - _from).y - 1;
	if (full < 0) full = 0;
	const unsigned int animationGridCount = (textureCols - _from.x) + (textureCols - _to.x) + full*textureCols;
	_animationFrameTime = animationTime / animationGridCount;
}

void Animation::update(float dt)
{
	_timeSinceLastAnimationFrame += dt;
	if (_timeSinceLastAnimationFrame > _animationFrameTime)
	{
		_timeSinceLastAnimationFrame = 0.0f;
		_currentFrame.x++;

		if (_currentFrame.y < _to.y)
		{
			if (_currentFrame.x == _texture->getGridSize().x)
			{
				_currentFrame.x = 0;
				_currentFrame.y++;
			}
		}
		else if (_currentFrame.y == _to.y)
		{
			if (_currentFrame.x == _texture->getGridSize().x)
			{
				_currentFrame = _from;
			}
		}
	}
}