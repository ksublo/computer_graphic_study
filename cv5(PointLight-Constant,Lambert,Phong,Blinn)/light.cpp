#include "Light.h"

Light::Light(LightType type, glm::vec3 position, glm::vec3 color, float intensity)
    : type(type), position(position), color(color), intensity(intensity) {}

void Light::setPosition(const glm::vec3& newPosition) {
    position = newPosition;
    notifyObservers();  
}

void Light::setColor(const glm::vec3& newColor) {
    color = newColor;
    notifyObservers(); 
}

void Light::setIntensity(float newIntensity) {
    intensity = newIntensity;
    notifyObservers();  
}

glm::vec3 Light::getPosition() const {
    return position;
}

glm::vec3 Light::getColor() const {
    return color;
}

float Light::getIntensity() const {
    return intensity;
}

LightType Light::getType() const {
    return type;
}
