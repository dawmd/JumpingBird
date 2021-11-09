#include "Pipe.h"

Pipe::Pipe(const GLfloat *init_position_)
    : Rectangle(init_position_)
    , shader("./pipeVertexShader.shader", "./pipeVertexShader.shader")
{}

void Pipe::use_shader() {
    shader.set_uniform("movement", 1, UniformDataType::MAT_4F, static_cast<const float *>(position));
    shader.set_uniform("projMatr", 1, UniformDataType::MAT_4F, static_cast<const float *>(Rectangle::projection_matrix));
}