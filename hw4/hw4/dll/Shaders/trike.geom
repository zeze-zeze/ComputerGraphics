#version 430 core
layout(triangles) in;
layout(line_strip, max_vertices = 6) out;

in VS_OUT {
    vec3 normal;
} gs_in[];

uniform mat4 P;

out vec4 color;

void GenerateLine(int index)
{
    if(index==0) color=vec4(1.0,0.0,0.0,1.0);
    else if(index==1) color=vec4(1.0,0.0,0.0,1.0);
    else color=vec4(1.0,0.0,0.0,1.0);
    gl_Position = gl_in[index].gl_Position ;
    EmitVertex();
    gl_Position = gl_in[index].gl_Position + vec4(gs_in[index].normal, 0.0f) * 0.2;
    EmitVertex();
    EndPrimitive();
}

void main()
{
    for(int i=0;i<gl_in.length();i++){
        GenerateLine(i);
    }
}
