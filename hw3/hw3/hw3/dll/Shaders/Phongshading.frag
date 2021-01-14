#version 430

uniform sampler2D texture;

in vec2 uv;
in vec3 normal;
in vec4 worldPos;

out vec4 color;

uniform vec3 WorldLightPos, WorldCamPos, Ka, Kd, Ks, La, Ld, Ls;
uniform int gloss;
void main()
{
    vec3 R, L, N, V;
    N = normal;
    L = normalize(WorldLightPos - worldPos.xyz);
    V = normalize(WorldCamPos - worldPos.xyz);
    R = normalize(reflect(-L, N));
    vec4 object_color = texture2D(texture, uv);
    vec3 ambient = La * Ka * object_color.xyz;
    vec3 diffuse = Ld * Kd * max(dot(L, N), 0) * object_color.xyz;
    vec3 specular = Ls * Ks * pow(max(dot(V, R), 0), gloss);
    color = vec4(ambient + diffuse + specular, 1);
} 