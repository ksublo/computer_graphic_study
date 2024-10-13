#pragma once
#include <GL/glew.h>
#include "Shader.h"
#include <glm/glm.hpp>

class ShaderProgram {
public:
    ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader);  
    bool setShaderProgram() const;  
    void use() const;  
    void setUniformMatrix4fv(const char* name, const glm::mat4& matrix) const;  

private:
    GLuint programID;  
};

