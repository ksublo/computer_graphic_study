#pragma once
#include <GL/glew.h>

class Shader {
public:
    Shader(const char* name, GLenum shaderType);    
    
    GLenum getType() const;

private: 
    GLenum type;  
    const char* name;
 
};
