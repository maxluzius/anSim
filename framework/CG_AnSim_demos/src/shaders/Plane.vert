#version 330 core

layout (location = 0) in vec4 Position;
layout (location = 2) in vec2 Tcoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec2 passTCoord;
 
void main(){

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * Position;
    passTCoord = Tcoord;
}
