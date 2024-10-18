#include "ShaderProgram.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

ShaderProgram::ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader) {
    programID = glCreateProgram(); 

    glAttachShader(programID, vertexShader.id);
    glAttachShader(programID, fragmentShader.id);
}

bool ShaderProgram::setShaderProgram() const{
    glLinkProgram(programID);  

    GLint isLinked = 0;
    glGetProgramiv(programID, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

        std::string infoLog(maxLength, '\0');
        glGetProgramInfoLog(programID, maxLength, &maxLength, &infoLog[0]);
        std::cerr << "Shader program linking failed: " << infoLog << std::endl;
        return false;  
    }

    return true;  
}

void ShaderProgram::use() const {
    glUseProgram(programID);  
}

void ShaderProgram::setUniformMatrix4fv(const char* name, const glm::mat4& matrix) const {
    GLint location = glGetUniformLocation(programID, name);
    if (location == -1) {
        std::cerr << "Could not find uniform variable '" << name << "' in shader program." << std::endl;
    }
    else {
        glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
    }
}

