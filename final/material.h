/**
 *
 * @file material.h
 *  @brief Represents material properties for objects, including ambient, diffuse, specular and shininess
 *
 * @author Kseniia Blokhina
 * @login BLO0021
 *
 */
#pragma once
#include <glm/glm.hpp>

class Material {
public:

    Material(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float shininess);

    glm::vec3 getAmbient() const;
    glm::vec3 getDiffuse() const;
    glm::vec3 getSpecular() const;
    float getShininess() const;

private:

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;

};
