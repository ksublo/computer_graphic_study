#pragma once
#include "Transformation.h"

class Translation : public Transformation {
public:
    Translation(float x, float y, float z);
    virtual glm::mat4 getMatrix() const override;

private:
    float x, y, z;
};
