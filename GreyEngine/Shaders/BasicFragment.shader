#version 330 core

layout(location = 0) out vec4 color;
in vec4 color_data;

in vec2 TexCoords;
uniform sampler2D tex0;
uniform vec4 lightColor;

void main()
{	
	if(TexCoords.x != -166)
        color = texture(tex0, TexCoords)*color_data*lightColor;
	else
		color = color_data*lightColor;
};