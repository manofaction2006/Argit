#version 330 core

layout(location=0)in vec3 i_Pos;
layout(location=1)in vec3 i_Color;
layout(location=2)in vec2 i_textCoord;

out vec3 o_color;
out vec2 o_textCoord;

uniform mat4 projection;

void main(){
	gl_Position = projection * vec4(i_Pos, 1.0f);
	o_color = i_Color;
	o_textCoord = i_textCoord;
}