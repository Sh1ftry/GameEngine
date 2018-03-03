#include "window.h"
#include <iostream>

int main()
{
	//game window
	Window window("Window", 800, 600);
	glClearColor(0.7f, 0.1f, 0.1f, 1.0f);

	//game loop
	while (!window.isClosed())
	{
		glClear(GL_COLOR_BUFFER_BIT);
		if (window.isKeyboardKeyPressed(GLFW_KEY_W))
			std::cout << "'W' is pressed!" << std::endl;
		if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
			std::cout << "LMB is pressed!" << std::endl;
		//update window state
		window.update();
	}

	return 0;
}