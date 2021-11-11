#pragma once

#include "Rectangle.h"
#include "Shader.h"
#include "Matrix4f.h"

class Bird : public Rectangle {
    private:
        float angle;
        Matrix4f rotation_matrix;
        Shader shader;
    public:
        Bird(const GLfloat *init_position_, const float init_angle);
        ~Bird() = default;
        
        void rotate(const float d_angle);
        float get_angle();
        void use_shader();
        void draw() override;
};
