#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 projMatr;

void main() {
  gl_Position = projMatr * position;
};
