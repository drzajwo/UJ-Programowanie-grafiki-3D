#version 410

layout(location=0) in vec3 vertex_position;
layout(location=1) in vec3 vertex_color;
out vec3 v_color;


layout(std140) uniform Intensity {
   float intensity;
};

layout(std140) uniform Transform {
	mat4 T;
};

void main()
{
	gl_Position = T*vec4(vertex_position, 1.f);
	v_color=vertex_color*intensity;
}
