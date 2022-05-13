#version 330 core

in vec3 o_color;
in vec2 o_textCoord;
in float o_textureIndex;

out vec4 color;

uniform sampler2D textures0;
uniform sampler2D textures1;
uniform sampler2D textures2;
uniform sampler2D textures3;
uniform sampler2D textures4;
uniform sampler2D textures5;
uniform sampler2D textures6;
uniform sampler2D textures7;
uniform sampler2D textures8;
uniform sampler2D textures9;
uniform sampler2D textures10;
uniform sampler2D textures11;
uniform sampler2D textures12;
uniform sampler2D textures13;
uniform sampler2D textures14;
uniform sampler2D textures15;

void main(){
	color = vec4(o_color,1.0f);

	int index = int(o_textureIndex);
	switch(index){
		case 0: color*=texture(textures0, o_textCoord); break;
		case 1: color*=texture(textures1, o_textCoord); break;
		case 2: color*=texture(textures2, o_textCoord); break;
		case 3: color*=texture(textures3, o_textCoord); break;
		case 4: color*=texture(textures4, o_textCoord); break;
		case 5: color*=texture(textures5, o_textCoord); break;
		case 6: color*=texture(textures6, o_textCoord); break;
		case 7: color*=texture(textures7, o_textCoord); break;
		case 8: color*=texture(textures8, o_textCoord); break;
		case 9: color*=texture(textures9, o_textCoord); break;
		case 10: color*=texture(textures10, o_textCoord); break;
		case 11: color*=texture(textures11, o_textCoord); break;
		case 12: color*=texture(textures12, o_textCoord); break;
		case 13: color*=texture(textures13, o_textCoord); break;
		case 14: color*=texture(textures14, o_textCoord); break;
		case 15: color*=texture(textures15, o_textCoord); break;

	}


}