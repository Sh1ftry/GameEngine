#version 330 core

layout (location = 0) out vec4 color;

in DATA
{
	vec4 color;
	vec4 position;
} fs_in;

uniform vec2 light_position;

void main()
{
	float intensity = 1.0f / length(fs_in.position.xy - light_position) * 50;
	color = fs_in.color * intensity;
}