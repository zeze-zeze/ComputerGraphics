#version 430

uniform sampler2D UFOTexture;
in vec4 color;
in vec2 tex;
out vec4 fragcolor;

void main()
{
	fragcolor = texture2D(UFOTexture, tex);
} 