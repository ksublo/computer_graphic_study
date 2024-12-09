/**
 *
 * @file scale.h
 * @brief Represents a scaling transformation in 3D space
 * 
 * @author Kseniia Blokhina
 * @login BLO0021
 *
 */
#pragma once
#include "Transformation.h"

class Scale : public Transformation {
public:

    Scale(float scaleFactor);
    virtual glm::mat4 getMatrix() const override;

private:

    float scaleFactor;
};
