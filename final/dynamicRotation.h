/**
 *
 * @file dynamicRotation.h
 * @brief Represents a dynamic rotation transformation, which continuously rotates an object at a specified speed
 *
 * @author Kseniia Blokhina
 * @login BLO0021
 *
 */
#pragma once
#include "Rotation.h"

class DynamicRotation : public Rotation {
public:

    DynamicRotation(float rotationSpeed, float x, float y, float z);
    void update(float deltaTime);

private:

    float rotationSpeed; 
};