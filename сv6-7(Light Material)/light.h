#pragma once
#include "Subject.h"
#include <glm/glm.hpp>

enum class LightType {
    POINT,
    DIRECTIONAL,
    SPOT
};

class Light : public Subject {
public:
    //POINT
    Light(LightType type, glm::vec3 position, glm::vec3 color, float intensity, float constant, float linear, float quadratic);

    //DIRECTIONAL
    Light(LightType type, glm::vec3 direction, glm::vec3 color, float intensity);

    //SPOT
    Light(LightType type, glm::vec3 position, glm::vec3 direction, glm::vec3 color, float intensity, float constant, float linear, float quadratic, float cutoff);


    void setPosition(const glm::vec3& newPosition);
    void setDirection(const glm::vec3& newDirecion);
    void setColor(const glm::vec3& newColor);
    void setIntensity(float newIntensity);
    void setAttenuationFactors(float constant, float linear, float quadratic);
    void setCutoff(float newCutoff);


    glm::vec3 getPosition() const;
    glm::vec3 getDirection() const;
    glm::vec3 getColor() const;
    float getIntensity() const;
    void getAttenuationFactors(float& constant, float& linear, float& quadratic) const;
    float getCutoff() const;

    LightType getType() const;

private:
    LightType type;


    glm::vec3 position; //POINT && SPOT
    glm::vec3 direction; //DIRECTIONAL && SPOT
    glm::vec3 color;
    float intensity;
    float cutoff; //SPOT

    //POINT && SPOT
    float constantFactor;
    float linearFactor;
    float quadraticFactor;
};
