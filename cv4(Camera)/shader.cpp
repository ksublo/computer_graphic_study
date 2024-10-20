#include "Shader.h"
#include <iostream>

Shader::Shader(const char* sourceCode, GLenum shaderType)
    : source(sourceCode), type(shaderType) {
    id = glCreateShader(type); 
}

Shader::~Shader() {
    glDeleteShader(id);  
}

void Shader::compile() const{
    glShaderSource(id, 1, &source, nullptr); 
    glCompileShader(id);  

    GLint isCompiled = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

        std::string infoLog(maxLength, '\0');
        glGetShaderInfoLog(id, maxLength, &maxLength, &infoLog[0]);
        std::cerr << "Shader compilation failed: " << infoLog << std::endl;
    }
}
