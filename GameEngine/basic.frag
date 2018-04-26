#version 330 core

layout (location = 0) out vec4 color;

uniform vec4 col;

void main()
{
	//float intensity = 1.0f / length(fs_in.position.xy - light_position) * 50;
	color = col;
}