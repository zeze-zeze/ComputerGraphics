#version 430

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 texcoord;

uniform mat4 M, V,P;
 
out VS_OUT {
    vec3 normal;
} vs_out;
out vec2 uv;

void main() {
  gl_Position = P * V * M * vec4(in_position, 1.0);
  vs_out.normal = normalize((transpose(inverse(M)) * vec4(in_normal, 1.0)).xyz);
  uv = texcoord;
}
