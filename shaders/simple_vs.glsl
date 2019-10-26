#version 330

layout(location=1) in vec3 vertex_color;
out vec3 v_color;
layout(location=0) in vec3 vertex_position;

void main()
{
	gl_Position = vec4(vertex_position, 1.f);
	v_color=vertex_color;
}
