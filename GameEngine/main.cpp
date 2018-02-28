#include "window.h"

int main()
{
	//game window
	Window window("Window", 800, 600);
	glClearColor(0.7f, 0.1f, 0.1f, 1.0f);

	//game loop
	while (!window.isClosed())
	{
		glClear(GL_COLOR_BUFFER_BIT);
		//update window state
		window.update();
	}

	return 0;
}