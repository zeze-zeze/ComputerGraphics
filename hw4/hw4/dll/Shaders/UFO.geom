#version 430
layout(triangles) in;
layout(line_strip, max_vertices = 6) out;

uniform float explosion;

in VS_OUT {
    vec3 normal;
    vec2 uv;
    vec2 mtlIndex;
} gs_in[];

//out vec2 uv_out;
//out vec4 color_in; 
out vec2 mtl;
out vec2 texcoord;
void main() {
    for(int i=0; i<gs_in.length(); i++){
        //uv_out = gs_in[i].uv;
        //color_in = vec4(1.0, 0, 0, 1);
        mtl = gs_in[i].mtlIndex;
        texcoord = gs_in[i].uv;
        //gl_Position = gl_in[i].gl_Position;
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
        gl_Position = gl_in[i].gl_Position + vec4(gs_in[i].normal, 0.0f) * 0.2;
        EmitVertex();
        EndPrimitive();
    }
}
