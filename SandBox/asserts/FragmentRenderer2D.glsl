#version 330 core

in vec3 o_color;
in vec2 o_textCoord;
in float o_textureIndex;

out vec4 color;

uniform sampler2D textures[16];

void main(){
	color = vec4(o_color,1.0f);

	int index = int(o_textureIndex);
	switch(index){
		case 0: color*=texture(textures[0], o_textCoord); break;
		case 1: color*=texture(textures[1], o_textCoord); break;
		case 2: color*=texture(textures[2], o_textCoord); break;
		case 3: color*=texture(textures[3], o_textCoord); break;
		case 4: color*=texture(textures[4], o_textCoord); break;
		case 5: color*=texture(textures[5], o_textCoord); break;
		case 6: color*=texture(textures[6], o_textCoord); break;
		case 7: color*=texture(textures[7], o_textCoord); break;
		case 8: color*=texture(textures[8], o_textCoord); break;
		case 9: color*=texture(textures[9], o_textCoord); break;
		case 10: color*=texture(textures[10], o_textCoord); break;
		case 11: color*=texture(textures[11], o_textCoord); break;
		case 12: color*=texture(textures[12], o_textCoord); break;
		case 13: color*=texture(textures[13], o_textCoord); break;
		case 14: color*=texture(textures[14], o_textCoord); break;
		case 15: color*=texture(textures[15], o_textCoord); break;

	}
}