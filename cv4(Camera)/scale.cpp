#include "Scale.h"
#include <glm/gtc/matrix_transform.hpp>

Scale::Scale(float scaleFactor)
    : scaleFactor(scaleFactor) {}

glm::mat4 Scale::getMatrix() const {
    return glm::scale(glm::mat4(1.0f), glm::vec3(scaleFactor));  
}
