#include "Rectangle.h"

Rectangle::Rectangle(const GLfloat *init_position_) {
    glGenVertexArrays(1, &vao_id);
    glBindVertexArray(vao_id);
    for (int i = 0; i < 2 * 4; ++i) {
        init_position[i] = init_position_[i];
    }
    glGenBuffers(1, &rectangle_id);
    glBindBuffer(GL_ARRAY_BUFFER, rectangle_id);
    glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), &init_position[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_id);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_UNSIGNED_BYTE, GL_TRUE, 2 * sizeof(unsigned char), 0);
    position.set_to_identity();
}

Rectangle::~Rectangle() {
    glDeleteBuffers(1, &rectangle_id);
}

void Rectangle::update(const float dx, const float dy, const float dz) {
    position.set_value(0, 3, position.get_element(0, 3) + dx);
    position.set_value(1, 3, position.get_element(1, 3) + dy);
    position.set_value(2, 3, position.get_element(2, 3) + dz);
}

void Rectangle::bind() {
    // glBindBuffer(GL_ARRAY_BUFFER, rectangle_id);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_id);
    glBindVertexArray(vao_id);
}

void Rectangle::draw() {
    bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
}

GLuint Rectangle::index_id;
bool Rectangle::index_allocated;
Matrix4f Rectangle::projection_matrix;