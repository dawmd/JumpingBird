#pragma once

#include <GL/glew.h>

#include <string>
#include <unordered_map>

enum class UniformDataType {
    FLOAT,        FLOAT_2,        FLOAT_3,        FLOAT_4,
    INT,          INT_2,          INT_3,          INT_4,
    UNSIGNED_INT, UNSIGNED_INT_2, UNSIGNED_INT_3, UNSIGNED_INT_4,
    MAT_2F,       MAT_3F,         MAT_4F,
    MAT_2x3F,     MAT_3x2F,
    MAT_2x4F,     MAT_4x2F,
    MAT_3x4F,     MAT_4x3F
};

class Shader {
    private:
        GLuint shaderID;
        std::unordered_map<std::string, GLint> uniforms;
    public:
        Shader(const std::string &vertex_shader_filepath, const std::string &fragment_shader_filepath);
        ~Shader();

        void bind() const;
        void unbind() const;

        /**
         * Sets the uniform to the given value. If the uniform of the given name doesn't exist,
         * returns @p false. Otherwise, returns @p true.
         */
        bool set_uniform(const std::string &uniform_name, const int count, UniformDataType data_type, const void *data);
    private:
        GLint get_uniform_location(const std::string &uniform_name);
};  