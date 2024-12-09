#include "Light.h"
#include <stdexcept>

Light::Light(LightType type, glm::vec3 position, glm::vec3 color, float intensity, float constant, float linear, float quadratic)
    : type(type), position(position), color(color), intensity(intensity),
    constantFactor(constant), linearFactor(linear), quadraticFactor(quadratic) {

    if (type != LightType::POINT) {
        throw std::invalid_argument("Invalid type for POINT light constructor.");
    }
}

Light::Light(LightType type, glm::vec3 direction, glm::vec3 color, float intensity)
    : type(type), direction(glm::normalize(direction)), color(color), intensity(intensity) {

    if (type != LightType::DIRECTIONAL) {
        throw std::invalid_argument("Invalid type for DIRECTIONAL light constructor.");
    }
}

Light::Light(LightType type, glm::vec3 position, glm::vec3 direction, glm::vec3 color, float intensity, float constant, float linear, float quadratic, float cutoff)
    : type(type), position(position), direction(glm::normalize(direction)), color(color), intensity(intensity),
    constantFactor(constant), linearFactor(linear), quadraticFactor(quadratic), cutoff(cutoff) {

    if (type != LightType::SPOT) {
        throw std::invalid_argument("Invalid type for SPOT light constructor.");
    }
}

//SETTERS
void Light::setPosition(const glm::vec3& newPosition) {
    position = newPosition;
    notifyObservers();  
}

void Light::setDirection(const glm::vec3& newDirecion)
{
    direction = newDirecion;
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

void Light::setAttenuationFactors(float constant, float linear, float quadratic) {
    constantFactor = constant;
    linearFactor = linear;
    quadraticFactor = quadratic;
    notifyObservers();
}

void Light::setCutoff(float newCutoff)
{
    cutoff = newCutoff;
    notifyObservers();
}

//GETTERS
glm::vec3 Light::getPosition() const {
    return position;
}

glm::vec3 Light::getDirection() const
{
    return direction;
}

glm::vec3 Light::getColor() const {
    return color;
}

float Light::getIntensity() const {
    return intensity;
}

void Light::getAttenuationFactors(float& constant, float& linear, float& quadratic) const {
    constant = constantFactor;
    linear = linearFactor;
    quadratic = quadraticFactor;
}

float Light::getCutoff() const
{
    return cutoff;
}

LightType Light::getType() const {
    return type;
}
