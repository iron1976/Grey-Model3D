#version 330 core

layout(location = 0) out vec4 color;
in vec4 color_data;

in vec2 TexCoords;
uniform sampler2D tex0;

void main()
{
	if(TexCoords.x != -166)
		color = texture(tex0, TexCoords);
	else
		color = color_data;
};