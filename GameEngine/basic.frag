#version 330 core

layout (location = 0) out vec4 color;
in vec4 col;

void main()
{
	color = col; //vec4(1.0, 0.0, 1.0, 1.0);
}