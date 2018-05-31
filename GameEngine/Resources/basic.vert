#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texturePosition;

out vec2 texPos;

uniform mat4 projection;
uniform mat4 view = mat4(1.0f);
uniform mat4 model = mat4(1.0f);

uniform vec2 tPos;
uniform vec4 tSize;

void main()
{
	gl_Position = projection * view * model * position;
	vec2 texPosition;
	
	if(tSize.z == 1.0f)
	{
		texPosition = vec2(1.0f - texturePosition.x, texturePosition.y);	
	}
	else
	{
		texPosition = texturePosition;	
	}

	if(tSize.w == 1.0f)
	{
		texPosition = vec2(texPosition.x, 1.0f - texPosition.y);
	}

	vec2 normalTexPos = texPosition * tSize.xy;
	texPos = normalTexPos + tPos;
}