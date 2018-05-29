#version 330 core

layout (location = 0) out vec4 color;

in vec2 texPos;

uniform vec4 col;
uniform sampler2D tex;

void main()
{
	vec4 sampled = vec4(1.0f, 1.0f, 1.0f, texture(tex, texPos).r);
    color = sampled * col;
}