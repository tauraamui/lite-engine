#version 410 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_tex_coord;
layout (location = 2) in vec3 a_v_normal;

out vec2 v_tex_coord;
out vec3 v_normal;
out vec3 v_fragment_position;

uniform mat4 u_mvp;

void main(){
	gl_Position = u_mvp * vec4(a_position, 1.0);
	v_tex_coord = a_tex_coord;
	v_normal = mat3(transpose(inverse(u_mvp))) * a_v_normal; //TODO this is EXPENSIVE! do it on the cpu instead
	v_fragment_position = vec3(u_mvp * vec4(a_position, 1.0));
} 
