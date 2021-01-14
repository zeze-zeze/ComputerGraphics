#version 430

uniform sampler2D TrikeTexture;
uniform int start;
in vec2 uv;
//in vec4 color;
out vec4 fragcolor;

void main()
{
	if (start == 0) fragcolor = texture2D(TrikeTexture, uv);
	else fragcolor = vec4(0, 0, 0, 0);
} 