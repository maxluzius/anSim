#version 330 core

//incoming data
in vec2 passTCoord;

uniform int useColorTexture;
uniform sampler2D colorTexture;

out vec4 fragmentColor;
 
void main(){

    fragmentColor = texture(colorTexture, passTCoord);
}
