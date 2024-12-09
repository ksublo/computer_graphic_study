/**
 *
 * @file translation.h
 * @brief Represents a translation transformation in 3D space.
 *
 * @author Kseniia Blokhina
 * @login BLO0021
 *
 */
#pragma once
#include "Transformation.h"

class Translation : public Transformation {
public:

    Translation(float x, float y, float z);
    virtual glm::mat4 getMatrix() const override;

private:

    float x, y, z;
};
