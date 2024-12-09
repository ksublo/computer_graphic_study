/**
 *
 * @file object.h
 * @brief Represents a 3D object defined by an array of vertices.
 * 
 * @author Kseniia Blokhina
 * @login BLO0021
 *
 */
#pragma once
#include <GL/glew.h>
#include "objectBase.h"

class Object: public ObjectBase {
public:

    Object(float* vertices, size_t size, int vertexCount);
    ~Object();

    void bind() override;
    void draw() override;

protected:

    GLuint VAO, VBO;
    int vertexCount;
};
