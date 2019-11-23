#version 330

out vec4 frag_color;
in vec3 v_color;
uniform sampler2D color;

void main()
{
	frag_color = texture(color, vec2(v_color.x, v_color.y));
}
