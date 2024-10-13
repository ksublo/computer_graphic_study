#include "Transformation.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Transformation::Transformation() : matrix(glm::mat4(1.0f)) {
    // identyfing
}

void Transformation::translate(float x, float y, float z) {
    matrix = glm::translate(matrix, glm::vec3(x, y, z));
}

void Transformation::rotate(float angle, float x, float y, float z) {
    matrix = glm::rotate(matrix, glm::radians(angle), glm::vec3(x, y, z));
}

void Transformation::scale(float a) {
    matrix = glm::scale(matrix, glm::vec3(a));
}

void Transformation::combine(const Transformation& other)
{
    matrix = matrix * other.matrix;
}

void Transformation::applyTransformation(ShaderProgram& shaderProgram, const char* uniformName) const {
    shaderProgram.setUniformMatrix4fv(uniformName, matrix);
}
