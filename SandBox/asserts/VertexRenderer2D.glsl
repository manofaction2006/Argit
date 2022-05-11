#version 330 core

layout(location=0)in vec3 i_pos;
layout(location=1)in vec3 i_color;
layout(location=2)in vec2 i_textCoord;
layout(location=3)in float i_textureIndex;

out vec3 o_color;
out vec2 o_textCoord;
out float o_textureIndex;

uniform mat4 projection;

void main(){
	gl_Position = projection * vec4(i_pos, 1.0f);
	o_color = i_color;
	o_textCoord = i_textCoord;
	o_textureIndex = i_textureIndex;
}