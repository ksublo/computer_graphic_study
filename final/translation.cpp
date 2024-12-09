#include "Translation.h"
#include <glm/gtc/matrix_transform.hpp>

Translation::Translation(float x, float y, float z)
    : x(x), y(y), z(z) {}

glm::mat4 Translation::getMatrix() const {
    return glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z)); 
}
