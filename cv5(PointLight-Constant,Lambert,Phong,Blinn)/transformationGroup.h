#pragma once
#include <vector>
#include "Transformation.h"

class TransformationGroup : public Transformation {
public:
    ~TransformationGroup();
    void addTransformation(Transformation* transformation);
    virtual glm::mat4 getMatrix() const override; 

private:
    std::vector<Transformation*> transformations;
};
