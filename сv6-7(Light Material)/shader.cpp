#include "Shader.h"
#include <iostream>

Shader::Shader(const char* name, GLenum shaderType)
    : type(shaderType) {}

GLenum Shader::getType() const
{
    return type;
}



