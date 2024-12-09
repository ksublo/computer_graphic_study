/**
 *
 * @file transforamtion.h
 * @brief Base class for various transformations in 3D space
 *
 * @author Kseniia Blokhina
 * @login BLO0021
 *
 */
#pragma once
#include <glm/glm.hpp>

class Transformation {
public:

    virtual ~Transformation() {}

    virtual glm::mat4 getMatrix() const = 0;
};
