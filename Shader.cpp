#include "Shader.h"

#include <iostream>

// For loading shaders from files
#include <fstream>
#include <sstream>

static std::string load_shader(const std::string &filepath) {
    std::ifstream stream(filepath);
    std::stringstream ss;
    std::string line;

    while (getline(stream, line)) {
      ss << line << "\n";
    }

    return ss.str();
}

static GLuint compile_shader(GLenum shader_type, const std::string &source_code) {
    GLuint shader_index = glCreateShader(shader_type);
    const char *src = source_code.c_str();
    glShaderSource(shader_index, 1, &src, nullptr);
    glCompileShader(shader_index);
    int compilation_result;
    glGetShaderiv(shader_index, GL_COMPILE_STATUS, &compilation_result);
    if (!compilation_result) {
        int length;
        glGetShaderiv(shader_index, GL_INFO_LOG_LENGTH, &length);
        char *error_message = new char[length + 1];

        if (error_message != nullptr) {
            glGetShaderInfoLog(shader_index, length, &length, error_message);
            error_message[length] = '\0';
            std::cerr << "Compilation failed: " << error_message << std::endl;
            delete [] error_message;
        }
        else {
            std::cerr << "Compilation of a shader failed. Cannot retrieve the error message.\n";
        }

        glDeleteShader(shader_index);
        return 0;
    }   
    return shader_index;
}

Shader::Shader(const std::string &vertex_shader_filepath = "",
               const std::string &fragment_shader_filepath = "")
{
    shaderID = glCreateProgram();
    GLuint vertex_shader = 0;
    GLuint fragment_shader = 0;
    if (vertex_shader_filepath.length() > 0) {
        vertex_shader = compile_shader(GL_VERTEX_SHADER, load_shader(vertex_shader_filepath));
    }
    if (fragment_shader_filepath.length() > 0) {
        fragment_shader = compile_shader(GL_FRAGMENT_SHADER, load_shader(fragment_shader_filepath));
    }   
    if (vertex_shader != 0) {
        glAttachShader(shaderID, vertex_shader);
    }
    if (fragment_shader != 0) {
        glAttachShader(shaderID, fragment_shader);
    }   
    glLinkProgram(shaderID);
    glValidateProgram(shaderID);    
    glDetachShader(shaderID, vertex_shader);
    glDetachShader(shaderID, fragment_shader);   
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

Shader::~Shader() {
    glDeleteProgram(shaderID);
}

void Shader::bind() const {
    glUseProgram(shaderID);
}

void Shader::unbind() const {
    glUseProgram(0);
}

bool Shader::set_uniform(const std::string &uniform_name, const int count, UniformDataType data_type, const void *data) {
    bind();
    const GLint uniform_location = get_uniform_location(uniform_name);
  
    switch (data_type) {
        case UniformDataType::FLOAT:
        glUniform1fv(uniform_location, (GLsizei) count, (const GLfloat *) data);
        break;
    case UniformDataType::FLOAT_2:
        glUniform2fv(uniform_location, (GLsizei) count, (const GLfloat *) data);
        break;
    case UniformDataType::FLOAT_3:
        glUniform3fv(uniform_location, (GLsizei) count, (const GLfloat *) data);
        break;
    case UniformDataType::FLOAT_4:
        glUniform4fv(uniform_location, (GLsizei) count, (const GLfloat *) data);
        break;
    case UniformDataType::INT:
        glUniform1iv(uniform_location, (GLsizei) count, (const GLint *) data);
        break;
    case UniformDataType::INT_2:
        glUniform2iv(uniform_location, (GLsizei) count, (const GLint *) data);
        break;
    case UniformDataType::INT_3:
        glUniform3iv(uniform_location, (GLsizei) count, (const GLint *) data);
        break;
    case UniformDataType::INT_4:
        glUniform3iv(uniform_location, (GLsizei) count, (const GLint *) data);
        break;
    case UniformDataType::UNSIGNED_INT:
        glUniform1uiv(uniform_location, (GLsizei) count, (const GLuint *) data);
        break;
    case UniformDataType::UNSIGNED_INT_2:
        glUniform2uiv(uniform_location, (GLsizei) count, (const GLuint *) data);
        break;
    case UniformDataType::UNSIGNED_INT_3:
        glUniform3uiv(uniform_location, (GLsizei) count, (const GLuint *) data);
        break;
    case UniformDataType::UNSIGNED_INT_4:
        glUniform4uiv(uniform_location, (GLsizei) count, (const GLuint *) data);
        break;
    case UniformDataType::MAT_2F:
        glUniformMatrix2fv(uniform_location, (GLsizei) count, GL_FALSE, (const GLfloat *) data);
        break;
    case UniformDataType::MAT_3F:
        glUniformMatrix3fv(uniform_location, (GLsizei) count, GL_FALSE, (const GLfloat *) data);
        break;
    case UniformDataType::MAT_4F:
        glUniformMatrix4fv(uniform_location, (GLsizei) count, GL_FALSE, (const GLfloat *) data);
        break;
    case UniformDataType::MAT_2x3F:
        glUniformMatrix2x3fv(uniform_location, (GLsizei) count, GL_FALSE, (const GLfloat *) data);
        break;
    case UniformDataType::MAT_3x2F:
        glUniformMatrix3x2fv(uniform_location, (GLsizei) count, GL_FALSE, (const GLfloat *) data);
        break;
    case UniformDataType::MAT_2x4F:
        glUniformMatrix2x4fv(uniform_location, (GLsizei) count, GL_FALSE, (const GLfloat *) data);
        break;
    case UniformDataType::MAT_4x2F:
        glUniformMatrix4x2fv(uniform_location, (GLsizei) count, GL_FALSE, (const GLfloat *) data);
        break;
    case UniformDataType::MAT_3x4F:
        glUniformMatrix3x4fv(uniform_location, (GLsizei) count, GL_FALSE, (const GLfloat *) data);
        break;
    case UniformDataType::MAT_4x3F:
        glUniformMatrix4x3fv(uniform_location, (GLsizei) count, GL_FALSE, (const GLfloat *) data);
        break;
    // Unknown type, error
    default:
        return false;
  }

  return true;
}

GLint Shader::get_uniform_location(const std::string &uniform_name) {
    if (uniforms.find(uniform_name) != uniforms.end()) {
        return uniforms[uniform_name];
    }
    else {
        GLint location = glGetUniformLocation(shaderID, uniform_name.c_str());
        uniforms[uniform_name] = location;
        return location;
    }
}
