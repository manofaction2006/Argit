#version 330 core

layout(location=0)in vec3 i_pos;
layout(location=1)in vec3 i_color;

out vec3 o_color;

uniform mat4 projection;

void main(){
	gl_Position = projection * vec4(i_pos, 1.0f);
	o_color = i_color;
}