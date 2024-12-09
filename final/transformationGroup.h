/**
 *
 * @file transformationGroup.h
 * @brief A group of transformations, which can contain multiple individual transformations and apply them collectively
 *
 * @author Kseniia Blokhina
 * @login BLO0021
 *
 */
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
