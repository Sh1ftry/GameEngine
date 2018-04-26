#version 330 core

layout (location = 0) in vec4 position;

uniform mat4 projection;
uniform mat4 view = mat4(1.0f);
uniform mat4 model = mat4(1.0f);

void main()
{
	gl_Position = projection * view * model * position;
}