/**
 *
 * @file texturedObject.h
 * @brief Represents a 3D object defined by an array of vertices, including texture coordinates
 * 
 * @author Kseniia Blokhina
 * @login BLO0021
 *
 */
#pragma once
#include "Object.h"
#include "Texture.h"

class TexturedObject : public Object {
public:

    TexturedObject(float* vertices, size_t size, int vertexCount);
};
