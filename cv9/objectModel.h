#pragma once
#include <string>
#include <vector>
#include "Texture.h" 
#include "Object.h"
#include "objectLoader.h"

class ObjectModel : public Object {
public:

    ObjectModel(const std::string& filePath, Texture* texture);
    void draw();
    void bind();

    int getTextureUnit() const;
private:
    GLuint VAO, VBO, IBO;
    Texture* texture;
    int indicesCount;
};