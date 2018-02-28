#include "window.h"
#include <iostream>

void windowResized(GLFWwindow* window, int height, int width);

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

	glfwSetWindowUserPointer(_window, this);
	glfwSetFramebufferSizeCallback(_window, windowResized);

}

Window::~Window()
{
	glfwTerminate();
}

void windowResized(GLFWwindow* window, int width, int height)
{
	Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
	win->setWidthAndHeight(width, height);
	std::cout << width << "x" << height << std::endl;
}

void Window::update()
{
	glfwPollEvents();
	//getting width and height
	glfwGetFramebufferSize(_window, &_width, &_height);
	//double buffering
	glfwSwapBuffers(_window);
}