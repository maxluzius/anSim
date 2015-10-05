#version 330 core

//incoming data
in vec3 passTexCoord;

//uniform sampler2D tex;
uniform samplerCube cubeMap;

out vec4 fragmentColor;
 
void main(){
	fragmentColor = texture(cubeMap, passTexCoord);
    //fragmentColor = texture(tex, passTexCoord);
}
