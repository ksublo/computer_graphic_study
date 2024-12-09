#include "TransformationGroup.h"

TransformationGroup::~TransformationGroup() {
    for (auto transformation : transformations) {
        delete transformation;
    }
}

void TransformationGroup::addTransformation(Transformation* transformation) {
    transformations.push_back(transformation);
}

glm::mat4 TransformationGroup::getMatrix() const {
    glm::mat4 combinedMatrix = glm::mat4(1.0f); 

    for (const auto& transformation : transformations) {
        combinedMatrix = transformation->getMatrix() * combinedMatrix;  
    }

    return combinedMatrix;  
}
