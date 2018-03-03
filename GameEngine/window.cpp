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

	//seting pointer associated with the created GLFW window to this class
	glfwSetWindowUserPointer(_window, this);

	//setting 'windowResized' function as a callback to window being resized
	glfwSetFramebufferSizeCallback(_window, windowResized);

	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		std::cout << "Could not initialize GLEW!" << std::endl;
	}

	std::cout << "OpenGL " << glGetString(GL_VERSION) << " is up and running!" << std::endl;

}

Window::~Window()
{
	glfwTerminate();
}

void windowResized(GLFWwindow* window, int width, int height)
{
	//its safe to assume that 'glfwGetWindowUserPointer' will
	//return pointer to valid Window object, because the object
	//exists as long as the GLFW is working
	Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
	win->setWidthAndHeight(width, height);
	std::cout << width << "x" << height << std::endl;
}

void Window::update()
{
	//process event waiting in event queue
	glfwPollEvents();
	//swapping buffers for double buffering
	glfwSwapBuffers(_window);
}