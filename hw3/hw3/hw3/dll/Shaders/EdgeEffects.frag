#version 430

uniform sampler2D texture;
uniform vec3 WorldCamPos;

in vec2 uv;
in vec3 normal;
in vec4 worldPos;

out vec4 color;
void main()
{
    color = texture2D(texture, uv);
    vec3 V = normalize(WorldCamPos - worldPos.xyz);
    float intensity = 1.0 - max(dot(V, normal), 0);
    if(intensity > 0.9) intensity = 1;
    else intensity = 0;
    vec3 color_edge =  intensity * vec3(1, 1, 1);
    color = vec4(color_edge, 1.0);
} 