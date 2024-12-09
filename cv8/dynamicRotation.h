#pragma once
#include "Rotation.h"

class DynamicRotation : public Rotation {
public:
    DynamicRotation(float rotationSpeed, float x, float y, float z);

    void update(float deltaTime);

private:
    float rotationSpeed; 
};