#include "texture.h"

Texture::Texture(const std::string& filePath, unsigned int unit): unit(unit)
{
    textureID = SOIL_load_OGL_texture(
        filePath.c_str(),
        SOIL_LOAD_RGBA,          
        SOIL_CREATE_NEW_ID,     
        SOIL_FLAG_INVERT_Y
    );

    if (textureID == 0) {
        std::cerr << "Failed to load texture: " << filePath << std::endl;
        exit(EXIT_FAILURE);
    }

    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0); 
}

Texture::Texture(const char* posx, const char* negx, const char* posy, const char* negy, const char* posz, const char* negz, unsigned int unit) : unit(unit) {
    textureID = SOIL_load_OGL_cubemap(
        posx, negx, posy, negy, posz, negz,
        SOIL_LOAD_RGB,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS
    );

    if (textureID == 0) {
        std::cerr << "Failed to load texture: " << std::endl;
        exit(EXIT_FAILURE);
    }

    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

Texture::~Texture() {
    glDeleteTextures(1, &textureID);
}

void Texture::use() const {
    glActiveTexture(GL_TEXTURE0 + unit); 
    glBindTexture(GL_TEXTURE_2D, textureID); 
}

int Texture::getUnit() {
    return unit;
}
