#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

/*
*	@brief Class responsible for handling shaders
*/
class Shader
{
private:
	GLuint _programID;
	GLint getUniformLocation(const GLchar* name) const;
public:
	/*
	*	@brief Loads and creates shaders
	*	@param vert vertex shader location
	*	@param frag fragment shader location
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

	
	/**
	 * @return program ID that runs shader
	 */
	GLuint getID() const { return _programID; };

	/**
	 * @brief Sets float uniform variable
	 * @param name location name
	 * @param value value to set at location
	 */
	void setUniform1f(const GLchar* name, float value) const;
	/**
	 * @brief Sets integer uniform variable
	 * @param name location name
	 * @param value value to set at location
	 */
	void setUniform1i(const GLchar* name, int value) const;
	/**
	 * @brief Sets vec2 uniform variable
	 * @param name location name
	 * @param vec2 vector to set at location
	 */
	void setUniform2f(const GLchar* name, const glm::vec2& vec2) const;
	/**
	 * @brief Sets vec3 uniform variable
	 * @param name location name
	 * @param vec3 vector to set at location
	 */
	void setUniform3f(const GLchar* name, const glm::vec3& vec3) const;
	/**
	 * @brief Sets vec4 uniform variable
	 * @param name location name
	 * @param vec4 vector to set at location
	 */
	void setUniform4f(const GLchar* name, const glm::vec4& vec4) const;
	/**
	 * @brief Sets mat4 uniform variable
	 * @param name location name
	 * @param mat4 matrix to set at location
	 */
	void setUniformMat4(const GLchar* name, const glm::mat4& mat4) const;


};