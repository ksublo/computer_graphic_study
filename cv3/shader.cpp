#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

void static checkCompileErrors(GLuint shader, std::string type) {
    GLint success;
    GLchar infoLog[1024];

    if (type != "PROGRAM") {
        // Проверка компиляции шейдера
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else {
        // Проверка линковки программы
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}

Shader::Shader(const char* vertexSource, const char* fragmentSource) {
    GLuint vertexShader = compileShader(vertexSource, GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShader(fragmentSource, GL_FRAGMENT_SHADER);

    // Проверка компиляции вершинного шейдера
    checkCompileErrors(vertexShader, "VERTEX");

    // Проверка компиляции фрагментного шейдера
    checkCompileErrors(fragmentShader, "FRAGMENT");

    programID = glCreateProgram();
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);

    // Проверка линковки программы
    checkCompileErrors(programID, "PROGRAM");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() {
    glDeleteProgram(programID);  
}

void Shader::use() const {
    glUseProgram(programID);  
}

void Shader::setUniformMatrix4fv(const char* name, const glm::mat4& matrix) const
{
    GLint location = glGetUniformLocation(programID, name);
    if (location == -1) {
        printf("Could not find uniform variable '%s'\n", name);
    }
    else {
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }
}


GLuint Shader::compileShader(const char* shaderSource, GLenum shaderType) {
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    return shader;
}



