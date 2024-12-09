/**
 *
 * @file rotation.h
 * @brief Represents a rotation transformation in 3D space.
 *
 * @author Kseniia Blokhina
 * @login BLO0021
 *
 */
#pragma once
#include "Transformation.h"

class Rotation : public Transformation {
public:

    Rotation(float angle, float x, float y, float z);
    virtual glm::mat4 getMatrix() const override;

protected:

    float angle;
    float axisX, axisY, axisZ;
};
