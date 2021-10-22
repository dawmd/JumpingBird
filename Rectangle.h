#pragma once

#include <GL/glew.h>

#include "Matrix4f.h"

class Rectangle {
    protected:
        static constexpr unsigned char indices[] = {
            0, 1, 2,
            2, 3, 0
        };
        static GLuint index_id;
        static bool index_allocated;
        static Matrix4f projection_matrix;
        GLuint vao_id;
        GLuint rectangle_id;
        GLfloat init_position[2 * 4];
        Matrix4f position;
    public:
        Rectangle(const GLfloat *init_position_);
        ~Rectangle();

        void update(const float dx, const float dy, const float dz);
    protected:
        void bind();
    public:
        virtual void draw();

        static void init_proj_matrix(const unsigned int window_width, const unsigned int window_height) {
            projection_matrix.set_to_identity();
            projection_matrix.set_value(0, 0, 2.0f / window_width);
            projection_matrix.set_value(1, 1, 2.0f / window_height);
        }

        static void init_indices() {
            glGenBuffers(1, &Rectangle::index_id);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Rectangle::index_id);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * 3 * sizeof(unsigned char), Rectangle::indices, GL_STATIC_DRAW);
            index_allocated = true;
        }

        static void free_indices() {
            if (index_allocated) {
                glDeleteBuffers(1, &Rectangle::index_id);
            }
        }
};