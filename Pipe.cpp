#include "Pipe.h"

// to be removed
#include <iostream>

Pipe::Pipe(const GLfloat *init_position_)
    : Rectangle(init_position_)
    , shader("./pipeVertexShader.shader", "./pipeFragmentShader.shader")
{
    std::cerr << "Created a pipe\n";
}

void Pipe::use_shader() {
    shader.bind();
    shader.set_uniform("movement", 1, UniformDataType::MAT_4F, static_cast<const float *>(position));
    shader.set_uniform("projMatr", 1, UniformDataType::MAT_4F, static_cast<const float *>(Rectangle::projection_matrix));
}

void Pipe::draw() {
    bind();
    use_shader();
    Rectangle::draw();
}