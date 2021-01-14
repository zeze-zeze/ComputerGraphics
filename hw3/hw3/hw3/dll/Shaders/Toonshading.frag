#version 430

uniform sampler2D texture;
uniform vec3 WorldLightPos, Kd;

in vec2 uv;
in vec3 normal;
in vec4 worldPos;

out vec4 color;
void main()
{
    vec4 object_color = texture2D(texture, uv);
    vec3 L = normalize(WorldLightPos - worldPos.xyz);
    float intensity;
    float level = dot(normal, L);
    if (level > 0.95) intensity = 1;
    else if (level > 0.75) intensity = 0.8;
    else if (level > 0.50) intensity = 0.6;
    else if (level > 0.25) intensity = 0.4;
    else intensity = 0.2;
    color = vec4(Kd * object_color.xyz * intensity, 1) ;
} 