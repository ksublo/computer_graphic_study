#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "subject.h" 

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera : public Subject {
public:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float yaw;
    float pitch;

    float movementSpeed;
    float mouseSensitivity;
    float zoom;

    Camera(glm::vec3 startPosition, glm::vec3 startUp, float startYaw, float startPitch);

    glm::mat4 getViewMatrix() const;
    glm::vec3 getPosition() const;
    glm::mat4 getProjectionMatrix() const;
    glm::vec3 getForward() const;

    void processKeyboard(Camera_Movement direction, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

    void resetPosition(const glm::vec3& newPosition, const glm::vec3& newTarget);

    void updateProjectionMatrix(float newAspectRatio);
private:

    void updateCameraVectors();
    glm::mat4 projection;
};

