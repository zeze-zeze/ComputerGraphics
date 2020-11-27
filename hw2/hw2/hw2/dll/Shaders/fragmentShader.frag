#version 430
//// TODO ////
//
// Hint:
// 1. Recieve texcoord and Normal from vertex shader
// 2. Calculate and return final color to opengl
//
uniform sampler2D Texture;

in vec2 frag_texcoord;

out vec4 color;
void main(){
	// bonus: color * 4
	color = 4 * texture2D(Texture, frag_texcoord);
} 
