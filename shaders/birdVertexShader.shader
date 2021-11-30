#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 movement;
uniform mat4 projMatr;
uniform mat4 rotMatr;

void main() {
  gl_Position = projMatr * movement * rotMatr * position;
};