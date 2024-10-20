#include "ShaderProgram.h"
#include <glm/gtc/type_ptr.hpp> 
#include <iostream>

ShaderProgram::ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader) : camera(nullptr) {
    programID = glCreateProgram();
    glAttachShader(programID, vertexShader.id);
    glAttachShader(programID, fragmentShader.id);
    glLinkProgram(programID);
}

bool ShaderProgram::setShaderProgram() const {
    glValidateProgram(programID);
    GLint status;
    glGetProgramiv(programID, GL_VALIDATE_STATUS, &status);
    return status == GL_TRUE;
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

void ShaderProgram::update() {
    if (camera) {
        use();  
        setUniformMatrix4fv("viewMatrix", camera->getViewMatrix());  
        setUniformMatrix4fv("projectionMatrix", camera->getProjectionMatrix());  
    }
}

void ShaderProgram::setCamera(Camera* cam) {
    this->camera = cam;
    camera->registerObserver(this);
}
