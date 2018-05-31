#pragma once

class KeyboardListener
{
public:
	virtual void keyPressed(int keycode) const = 0;
	virtual void keyReleased(int keycode) const = 0;
	virtual ~KeyboardListener() = default;
};