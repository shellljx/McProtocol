#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in mat4 model;
//layout (location = 2) in vec4 modelCol1;
//layout (location = 3) in vec4 modelCol2;
//layout (location = 4) in vec4 modelCol3;
layout (location = 5) in vec4 texture_coords;

out vec2 TexCoord;

uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	if(gl_VertexID==1||gl_VertexID==6){
	TexCoord = vec2(texture_coords[0],texture_coords[3]);
	}else if(gl_VertexID==2){
	TexCoord = vec2(texture_coords[2], texture_coords[1]);
	} else if (gl_VertexID==3||gl_VertexID==4){
	TexCoord = vec2(texture_coords[0], texture_coords[1]);
	}else{
	TexCoord = vec2(texture_coords[2],texture_coords[3]);
	}

}
