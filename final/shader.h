/**
 *
 * @file shader.h
 *
 * @author Kseniia Blokhina
 * @login BLO0021
 *
 */
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
