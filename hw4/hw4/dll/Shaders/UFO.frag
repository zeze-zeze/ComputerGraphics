#version 430

uniform sampler2D UFOTexture;
uniform int start;
in vec2 tex;
//in vec2 uv_out;
//in vec4 color_in;
out vec4 color;

void main()
{
	if(start == 0) color = texture2D(UFOTexture, tex);
	else color = vec4(0, 0, 0, 0);
} 
