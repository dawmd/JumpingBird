#FRAGMENT

#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 projMatr;

void main() {
  gl_Position = projMatr * position;
};

#VERTEX

#version 330 core

layout(location = 0) out vec4 color;

void main() {
  color = vec4(1.0, 0.0, 1.0, 1.0);
};