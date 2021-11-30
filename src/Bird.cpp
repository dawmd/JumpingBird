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
    , shader("./shaders/birdVertexShader.shader", "./shaders/birdFragmentShader.shader")
{
    angle = init_angle;
    rotation_matrix.set_to_identity();
    set_angle(rotation_matrix, angle);
}

void Bird::rotate(const float d_angle) {
    angle += d_angle;
    set_angle(rotation_matrix, angle);
}

float Bird::get_angle() {
    return angle;
}

void Bird::use_shader() {
    shader.bind();
    shader.set_uniform("movement", 1, UniformDataType::MAT_4F, static_cast<const float *>(position));
    shader.set_uniform("projMatr", 1, UniformDataType::MAT_4F, static_cast<const float *>(Rectangle::projection_matrix));
    shader.set_uniform("rotMatr", 1, UniformDataType::MAT_4F, static_cast<const float *>(rotation_matrix));
}

void Bird::draw() {
    bind();
    use_shader();
    Rectangle::draw();
}

void Bird::get_coordinates(std::array<float, 8> &result) const {
    Matrix4f mapping_matrix = Rectangle::projection_matrix * position * rotation_matrix;
    // (x_1, y_1), (x_2, y_2), (x_3, y_3), (x_4, y_4)
    // down-left corner, down-right corner, top-right corner. top-left corner
    // (when looking at the original state of the rectangle, without rotations)

    for (int i = 0; i < 4; ++i) {
        result[2 * i] = init_position[2 * i] * mapping_matrix.get_element(0, 0)
                        + init_position[2 * i + 1] * mapping_matrix.get_element(0, 1);

        result[2 * i + 1] = init_position[2 * i] * mapping_matrix.get_element(1, 0)
                          + init_position[2 * i + 1] * mapping_matrix.get_element(1, 1);
    }
}
