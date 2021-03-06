#include "Pipe.h"

Pipe::Pipe(const GLfloat *init_position_)
    : Rectangle(init_position_)
    , shader("./shaders/pipeVertexShader.shader", "./shaders/pipeFragmentShader.shader")
{}

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

float Pipe::get_x_coord() const {
    return position.get_element(0, 3);
}

float Pipe::get_y_coord() const {
    return position.get_element(1, 3);
}