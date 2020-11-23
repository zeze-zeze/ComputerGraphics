#version 430

layout(location = 0) in vec3 position;

uniform mat4 Projection;
uniform mat4 ModelView;

out vec3 color;

void main() {
  gl_Position = Projection * ModelView * vec4(position, 1.0);
  color = vec3(1.0, 0.0, 0.0);
}
