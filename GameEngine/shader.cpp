#include <string>
#include <iostream>
#include "shader.h"
#include "file_reader.h"

Shader::Shader(const char * vert, const char * frag)
{
	//reading vertex and fragment shader source codes
	std::string vertexSource, fragmentSource;
	
	if (!FileReader::readFile(vert, vertexSource))
	{
		std::cout << "Vertex shader not found!" << std::endl;
	}

	if(!FileReader::readFile(frag, fragmentSource))
	{
		std::cout << "Fragment shader not found!" << std::endl;
	}

	//creating program for shaders
	_programID = glCreateProgram();
	GLuint vertexID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentID = glCreateShader(GL_FRAGMENT_SHADER);

	//loading and compiling vertex and fragment shader
	const char* vertexSourceChar = vertexSource.c_str();
	glShaderSource(vertexID, 1, &vertexSourceChar, NULL);
	glCompileShader(vertexID);
	
	//checking for errors
	GLint resultCode;
	char resultBuffer[1024];
	glGetShaderiv(vertexID, GL_COMPILE_STATUS, &resultCode);
	if (resultCode == GL_FALSE)
	{
		glGetShaderInfoLog(vertexID, 1024, 0, resultBuffer);
		std::cout << "Could not compile vertex shader\n" << resultBuffer;
		glDeleteShader(vertexID);
		glDeleteShader(fragmentID);
		return;
	}

	//fragment creation 
	const char* fragmentSourceChar = fragmentSource.c_str();
	glShaderSource(fragmentID, 1, &fragmentSourceChar, NULL);
	glCompileShader(fragmentID);
	
	//checking for errors
	glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &resultCode);
	if (resultCode == GL_FALSE)
	{
		glGetShaderInfoLog(fragmentID, 1024, 0, resultBuffer);
		std::cout << "Could not compile fragment shader\n" << resultBuffer;
		glDeleteShader(vertexID);
		glDeleteShader(fragmentID);
		return;
	}

	//attaching and linking shaders to program
	glAttachShader(_programID, vertexID);
	glAttachShader(_programID, fragmentID);
	glLinkProgram(_programID);
	glValidateProgram(_programID);

	//freeing memory
	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);

}

Shader::~Shader()
{
	glDeleteProgram(_programID);
}

void Shader::enable() const
{
	glUseProgram(_programID);
}

void Shader::disable() const
{
	glUseProgram(0);
}