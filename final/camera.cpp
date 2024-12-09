#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>  
#include <iostream>
#include <glm/glm.hpp> 


Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, float startYaw, float startPitch)
    : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(2.5f), mouseSensitivity(0.1f), zoom(60.0f) {
    position = startPosition;
    worldUp = startUp;
    yaw = startYaw;
    pitch = startPitch;
    updateCameraVectors();

    projection = glm::perspective(glm::radians(zoom), 4.0f / 3.0f, 0.1f, 100.0f);
}

glm::mat4 Camera::getViewMatrix() const{
    return glm::lookAt(position, position + front, up);
}

glm::vec3 Camera::getPosition() const {
    return position;
}

void Camera::processKeyboard(Camera_Movement direction, float deltaTime) {
    float velocity = movementSpeed * deltaTime;
    if (direction == FORWARD)
        position += front * velocity;
    if (direction == BACKWARD)
        position -= front * velocity;
    if (direction == LEFT)
        position -= right * velocity;
    if (direction == RIGHT)
        position += right * velocity;

    notifyObservers();
}

void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (constrainPitch) {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    updateCameraVectors();
    notifyObservers();
}

void Camera::updateCameraVectors() {
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(newFront);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

glm::mat4 Camera::getProjectionMatrix() const {
    return projection;
}

glm::vec3 Camera::getForward() const {
    return glm::normalize(front);
}

void Camera::resetPosition(const glm::vec3& newPosition, const glm::vec3& newTarget) {
    position = newPosition;
    front = glm::normalize(newTarget - newPosition);
    updateCameraVectors();
}

void Camera::updateProjectionMatrix(float newAspectRatio) {
    projection = glm::perspective(glm::radians(zoom), newAspectRatio, 0.1f, 100.0f);
}

glm::ivec2 Camera::getResolution() const {
    return resolution; 
}

void Camera::setResolution(int width, int height) {
    resolution = glm::ivec2(width, height);
    updateProjectionMatrix(static_cast<float>(width) / height);
}