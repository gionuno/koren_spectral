#version 130

in vec3 v_x;

uniform mat4 PM;

out vec3 f_x;

void main()
{
	f_x = vec3(PM*vec4(v_x,1.0));
	gl_Position = vec4(f_x,1.);
}
