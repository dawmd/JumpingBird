#pragma once

#include "Rectangle.h"
#include "Shader.h"

class Pipe : public Rectangle {
    private:
        Shader shader;
    public:
        Pipe(const GLfloat *init_position_);
        ~Pipe() = default;

        void use_shader();
        void draw() override;
        float get_x_coord() const;
};
