#version 330 core

layout(location = 0) in vec3 position;
uniform vec3 objectScale;
uniform vec3 objectPosition;

uniform vec2 Invert;
uniform mat4 view;
uniform mat4 ortho;
uniform float layer;

out vec4 color_data;
uniform int UseTex;


uniform vec4 custom_color;
out vec2 TexCoords;

vec2 TexCoordsVer[6] = vec2[6]
(
vec2(-0.5f, -0.5f),vec2(-0.5f, 0.5f),vec2(0.5f, 0.5f),  
vec2(0.5f, -0.5f), vec2(0.5f, 0.5f), vec2(-0.5f, -0.5f)
);


void main()
{
	gl_Position = view*ortho*vec4((position + objectPosition) * objectScale, 1.0f);
	color_data = custom_color;
	
	if (UseTex == 1)
		TexCoords = (TexCoordsVer[gl_VertexID] / (Invert*vec2(1,1))) + vec2(0.5f, 0.5f);
	else
		TexCoords = vec2(-166, -1);
};

