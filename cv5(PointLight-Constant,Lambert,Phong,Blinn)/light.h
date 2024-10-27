#pragma once
#include "Subject.h"
#include <glm/glm.hpp>

enum class LightType {
    POINT
};

class Light : public Subject {
public:
    Light(LightType type, glm::vec3 position, glm::vec3 color, float intensity);

    void setPosition(const glm::vec3& newPosition);
    void setColor(const glm::vec3& newColor);
    void setIntensity(float newIntensity);

    glm::vec3 getPosition() const;
    glm::vec3 getColor() const;
    float getIntensity() const;
    LightType getType() const;

private:
    LightType type;
    glm::vec3 position;
    glm::vec3 color;
    float intensity;
};
