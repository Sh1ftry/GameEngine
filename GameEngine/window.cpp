#include "window.h"
#include <iostream>
#include <GL/glew.h>

void windowResized(GLFWwindow* window, int height, int width);
void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouseCallback(GLFWwindow* window, int button, int action, int modes);
void mouseCursorCallback(GLFWwindow* window, double xpos, double ypos);

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

	//turning off vsync
	glfwSwapInterval(0);

	glEnable(GL_BLEND);// you enable blending function
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//setting mouse and keyboard callbacks;
	glfwSetMouseButtonCallback(_window, mouseCallback);
	glfwSetKeyCallback(_window, keyboardCallback);
	glfwSetCursorPosCallback(_window, mouseCursorCallback);

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
	//showing errors
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		//std::cout << "OpenGL error: " << err << std::endl;
	}
}

void Window::keyboardKeyPressed(unsigned int code)
{
	if (code < MAX_KEYS)
	{
		_keyboardKeys[code] = true;
	}
	else
	{
		return;
	}
}

void Window::keyboardKeyReleased(unsigned int code)
{
	if (code < MAX_KEYS)
	{
		_keyboardKeys[code] = false;
	}
	else
	{
		return;
	}
}

bool Window::isKeyboardKeyPressed(unsigned int code) const
{
	if (code < MAX_KEYS)
	{
		return _keyboardKeys[code];
	}
	else
	{
		return false;
	}
}

void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
	if (action != GLFW_RELEASE) win->keyboardKeyPressed(key);
	else win->keyboardKeyReleased(key);
}

void Window::mouseButtonPressed(unsigned int code)
{
	if (code < MAX_BUTTONS)
	{
		_mouseButtons[code] = true;
	}
	else
	{
		return;
	}
}

void Window::mouseButtonReleased(unsigned int code)
{
	if (code < MAX_BUTTONS)
	{
		_mouseButtons[code] = false;
	}
	else
	{
		return;
	}
}

bool Window::isMouseButtonPressed(unsigned int code) const
{
	if (code < MAX_BUTTONS)
	{
		return _mouseButtons[code];
	}
	else
	{
		return false;
	}
}

void mouseCallback(GLFWwindow* window, int button, int action, int modes)
{
	Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
	if (action != GLFW_RELEASE) win->mouseButtonPressed(button);
	else win->mouseButtonReleased(button);
}

void Window::setMouseCursorPosition(double xpos, double ypos)
{
	_x = xpos;
	_y = ypos;
}

void Window::getMouseCursorPosition(double& xpos, double& ypos) const
{
	xpos = _x;
	ypos = _y;
}

void mouseCursorCallback(GLFWwindow* window, double xpos, double ypos)
{
	Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
	win->setMouseCursorPosition(xpos, ypos);
}
