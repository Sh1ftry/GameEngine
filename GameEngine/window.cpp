#include "window.h"
#include <iostream>

Window::Window(const char* name, int width, int height) 
	: _name(name), _width(width), _height(height)
{

	//glfw iunitalization
	if (!glfwInit())
	{
		std::cout << "Could not initialize GLFW!";
		return;
	}

	//window creation
	_window = glfwCreateWindow(_width, _height, _name, NULL, NULL);
	if (!_window)
	{
		glfwTerminate();
		std::cout << "Could not create window!";
		return;
	}

	//registering opengl context to window
	glfwMakeContextCurrent(_window);

}

Window::~Window()
{
	glfwTerminate();
}

void Window::update()
{
	glfwPollEvents();
	//getting width and height
	glfwGetFramebufferSize(_window, &_width, &_height);
	//double buffering
	glfwSwapBuffers(_window);
}