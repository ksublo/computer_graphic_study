/**
 *
 * @file objectModel.h\
 * @brief Represents a 3D object loaded from an OBJ file
 *
 * @author Kseniia Blokhina
 * @login BLO0021
 *
 */
#pragma once
#include <string>
#include <vector>
#include "Texture.h"
#include "Object.h"
#include "objectLoader.h"

class ObjectModel : public ObjectBase {
public:

    ObjectModel(const std::string& filePath);
    ~ObjectModel();

    void draw() override;
    void bind() override;

private:

    GLuint VAO, VBO, IBO;
    int indicesCount;  
};
