#pragma once
#include <GL\glew.h>

/*
*	@brief Class responsible for handling shaders
*/
class Shader
{
private:
	GLuint _programID;
public:
	/*
	*	@brief Loads and creates shaders
	*/
	Shader(const char* vert, const char* frag);
	/*
	*	@brief Terminates shaders program
	*/
	~Shader();

	/*
	*	@brief Enables vertex and fragment shader
	*/
	void enable() const;
	/*
	*	@brief Disables vertex and fragment shader
	*/
	void disable() const;

	GLuint getID() { return _programID; };

};