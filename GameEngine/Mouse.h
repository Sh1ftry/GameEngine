#pragma once
#define MAX_BUTTONS 32
class Mouse
{
private:
	bool _buttons[32];
	double x, y;
public:
	bool isButtonPressed(unsigned int code) const;
};