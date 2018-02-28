#pragma once
#include <GLFW\glfw3.h>

/*
*
*	@brief Class responsible for handling GLFW window
*
*/
class Window {
private:
	const char* _name;
	int _height, _width;
	GLFWwindow* _window;
public:
	/*
	*	@brief Costructor initializes GLFW and creates window
	*	@param[in] name Title of the window
	*	@param[in] width Width of the window
	*	@param[in] height Height of the window
	*/
	Window(const char* name, int width, int height);
	/*
	*	@brief Destructor terminates GLFW
	*/
	~Window();
	/*
	*	@brief Updating window state
	*/
	void update();
	/*
	*	@return false if window is not closed, true if window is closed
	*/
	bool isClosed() const { return glfwWindowShouldClose(_window); }

	/*
	*	@return Width of the window
	*/
	int getWidth() const { return _width; };
	/*
	*	@return Height of the window
	*/
	int getHeight() const { return _height; };

};