/**
 *
 * @file skyboxObject.h
 * @brief Represents a 3D skybox defined by vertices
 * 
 * @author Kseniia Blokhina
 * @login BLO0021
 *
 */
#pragma once
#include "Object.h"
#include "Texture.h" 

class SkyboxObject : public Object {
public:

    SkyboxObject(float* vertices, size_t size, int vertexCount);

};