#include "DynamicRotation.h"

DynamicRotation::DynamicRotation(float rotationSpeed, float x, float y, float z)
    : Rotation(0.0f, x, y, z), rotationSpeed(rotationSpeed) {}

void DynamicRotation::update(float deltaTime) {
    angle += rotationSpeed * deltaTime;

    if (angle >= 360.0f) {
        angle -= 360.0f;
    }
}

