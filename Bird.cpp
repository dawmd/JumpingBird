#include "Bird.h"

#include <cmath>

static void set_angle(Matrix4f &rotation_matrix, const float angle) {
    const float radians = angle * M_PI / 180.0f;
    const float sin = std::sin(radians);
    const float cos = std::cos(radians);
    rotation_matrix.set_value(0, 0, cos);
    rotation_matrix.set_value(0, 1, (-1.0f) * sin);
    rotation_matrix.set_value(1, 0, sin);
    rotation_matrix.set_value(1, 1, cos);
}

// #include <iostream>

Bird::Bird(const GLfloat *init_position_, const float init_angle)
    : Rectangle(init_position_)
    , shader("./birdVertexShader.shader", "./birdFragmentShader.shader")
{
    // for (int i = 0; i < 8; ++i) {
    //     std::cout << "pos[" << i << "] = " << init_position_[i] << "\n";
    // }
    bind();
    shader.bind();
    angle = init_angle;
    rotation_matrix.set_to_identity();
    set_angle(rotation_matrix, angle);
}

void Bird::rotate(const float d_angle) {
    angle += d_angle;
    set_angle(rotation_matrix, angle);
}

void Bird::use_shader() {
    shader.bind();
    shader.set_uniform("movement", 1, UniformDataType::MAT_4F, static_cast<const float *>(position));
    shader.set_uniform("projMatr", 1, UniformDataType::MAT_4F, static_cast<const float *>(Rectangle::projection_matrix));
    shader.set_uniform("rotMatr", 1, UniformDataType::MAT_4F, static_cast<const float *>(rotation_matrix));
}

void Bird::draw() {
    // std::cout << "Draw:\n";
    // for (int i = 0; i < 4; ++i) {
    //     for (int j = 0; j < 4; ++j) {
    //         std::cout << "mat[" << i << "][" << j << "] = " << position.get_element(i, j) << ", ";
    //     }
    //     std::cout << "\n";
    // }
    // std::cout << "ProjMat:\n";
    // for (int i = 0; i < 4; ++i) {
    //     for (int j = 0; j < 4; ++j) {
    //         std::cout << "mat[" << i << "][" << j << "] = " << Rectangle::projection_matrix.get_element(i, j) << ", ";
    //     }
    //     std::cout << "\n";
    // }
    // std::cout << "RotMat:\n";
    // for (int i = 0; i < 4; ++i) {
    //     for (int j = 0; j < 4; ++j) {
    //         std::cout << "mat[" << i << "][" << j << "] = " << rotation_matrix.get_element(i, j) << ", ";
    //     }
    //     std::cout << "\n";
    // }
    // std::cout << "initpos:\n";
    // for (int i = 0; i < 8; ++i) {
    //     std::cout << "init[" << i << "] = " << init_position[i] << "\n";
    // }
    bind();
    use_shader();
    Rectangle::draw();
}
