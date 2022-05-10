#version 330 core

layout(location=0)in vec3 i_Pos;
layout(location=1)in vec3 i_Color;

out vec3 o_color;

void main(){
	gl_Position = vec4(i_Pos, 1.0f);
	o_color = i_Color;
}