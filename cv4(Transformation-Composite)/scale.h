#pragma once
#include "Transformation.h"

class Scale : public Transformation {
public:
    Scale(float scaleFactor);
    virtual glm::mat4 getMatrix() const override;

private:
    float scaleFactor;
};
