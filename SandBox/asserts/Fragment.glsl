#version 330 core

in vec3 o_color;
in vec2 o_textCoord;

out vec4 color;

uniform sampler2D text;

void main(){
	color = vec4(o_color, 1.0f) * texture(text, o_textCoord);
}