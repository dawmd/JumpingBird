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

Bird::Bird(const GLfloat *init_position_, const float init_angle)
    : Rectangle(init_position_)
    , shader("./birdVertexShader.shader", "./birdFragmentShader.shader")
{
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
    // shader.bind();
    shader.set_uniform("movement", 1, UniformDataType::MAT_4F, (const void *) position);
    shader.set_uniform("projMatr", 1, UniformDataType::MAT_4F, (const void *) Rectangle::projection_matrix);
    shader.set_uniform("rotMatr", 1, UniformDataType::MAT_4F, (const void *) rotation_matrix);
}

void Bird::draw() {
    bind();
    use_shader();
    Rectangle::draw();
}