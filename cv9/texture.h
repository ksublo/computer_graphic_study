#pragma once
#include <GL/glew.h>
#include <SOIL.h>
#include <string>
#include <iostream>

class Texture {
public:
    Texture(const std::string& filePath, unsigned int unit);
    Texture(const char* posx, const char* negx, const char* posy, const char* negy, const char* posz, const char* negz, unsigned int unit);
    ~Texture();

    void use() const;
    int getUnit();

private:
    GLuint textureID;
    unsigned int unit;
};
