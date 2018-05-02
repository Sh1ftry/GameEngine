#version 330 core

layout (location = 0) out vec4 color;

in vec2 texPos;

uniform vec4 col;
uniform sampler2D tex;

void main()
{
	//float intensity = 1.0f / length(fs_in.position.xy - light_position) * 50;
	color = texture(tex, texPos);
}