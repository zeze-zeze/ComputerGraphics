#version 430 core
layout(triangles) in;
layout(line_strip, max_vertices = 6) out;
uniform float explosion;
uniform int start;
in VS_OUT {
    vec3 normal;
    vec2 tex;
} gs_in[];

uniform mat4 P;

out vec4 color;
out vec2 tex;
void GenerateLine(int index)
{
    tex = gs_in[index].tex;
    gl_Position = gl_in[index].gl_Position + vec4(gs_in[index].normal, 0.0f) * explosion * start;
    EmitVertex();
    gl_Position = gl_in[index].gl_Position + vec4(gs_in[index].normal, 0.0f) * (explosion + 0.2) * start;
    EmitVertex();
    EndPrimitive();
}

void main()
{
    for(int i=0;i<gl_in.length();i++){
        GenerateLine(i);
    }
}
