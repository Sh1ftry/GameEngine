#pragma once
#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include <unordered_map>
#include "keyboard_listener.h"

/*
*	@brief Max mouse buttons
*/
#define MAX_BUTTONS 32
#define MAX_KEYS 1024

/*
*
*	@brief Class responsible for handling GLFW window
*
*/
class Window
{
private:
	const char* _name;
	int _height, _width;
	GLFWwindow* _window;

	//mouse buttons array
	bool _mouseButtons[MAX_BUTTONS];
	//mouse cursor position
	double _x, _y;

	//keyboard keys array
	bool _keyboardKeys[MAX_KEYS];

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

	/*
	*	@brief Sets width and height of window. Does not resize window
	*	@param[in] width New width value
	*	@param[in] height New height value
	*/
	void setWidthAndHeight(int width, int height) { _width = width; _height = height; }

	/*
	*	@brief Sets keyboard key as pressed
	*	@param[in] code Code of pressed key
	*/
	void keyboardKeyPressed(unsigned int code);
	/*
	*	@brief Sets keyboard key as released
	*	@param[in] code Code of released key
	*/
	void keyboardKeyReleased(unsigned int code);
	/*
	*	@brief Checks if keyboard key is pressed
	*	@param[in] code Code of key to check
	*	@return true if key is pressed, otherwise false
	*/
	bool isKeyboardKeyPressed(unsigned int code) const;
	/*
	*	@brief Sets mouse button as pressed
	*	@param[in] code Code of pressed button
	*/
	void mouseButtonPressed(unsigned int code);
	/*
	*	@brief Sets mouse button as released
	*	@param[in] code Code of released button
	*/
	void mouseButtonReleased(unsigned int code);
	/*
	*	@brief Checks if mouse button is pressed
	*	@param[in] code Code of button to check
	*	@return true if button is pressed, otherwise false
	*/
	bool isMouseButtonPressed(unsigned int code) const;
	/*
	*	@brief Sets position of mouse cursor
	*	@param[in] x Value of x
	*	@param[in] y Value of y
	*/
	void setMouseCursorPosition(double x, double y);
	/*
	*	@param[out] x Value of x
	*	@param[out] y Value of y
	*	@return Position of mouse cursor
	*/
	void getMouseCursorPosition(double& x, double& y) const;

};