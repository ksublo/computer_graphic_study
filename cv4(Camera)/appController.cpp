#include "AppController.h"
#include <iostream>

AppController::AppController(Scene& scene1, Scene& scene2, Camera* camera)
    : scene(scene1), scene1(scene2), camera(camera) {}

//SCENE
void AppController::switchScene(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS && key == GLFW_KEY_T) {
        sceneActive = !sceneActive;
        std::cout << "Scene switched!" << std::endl;
    }
}

//TRANSFORMATIONS
void AppController::rotatateY(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS && key == GLFW_KEY_R) {
        rotationActive = !rotationActive;
        std::cout << "Rotation toggled!" << std::endl;
    }
}

void AppController::translate(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        float translateAmount = 0.05f;
        if (key == GLFW_KEY_RIGHT) {
            applyTranslationToScene(sceneActive ? scene : scene1, translateAmount, 0.0f);
        }
        else if (key == GLFW_KEY_LEFT) {
            applyTranslationToScene(sceneActive ? scene : scene1, -translateAmount, 0.0f);
        }
        else if (key == GLFW_KEY_UP) {
            applyTranslationToScene(sceneActive ? scene : scene1, 0.0f, translateAmount);
        }
        else if (key == GLFW_KEY_DOWN) {
            applyTranslationToScene(sceneActive ? scene : scene1, 0.0f, -translateAmount);
        }
    }
}

//CAMERA
void AppController::cameraWSAD(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (camera == nullptr) return;  

    float deltaTime = 0.016f; 

    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        if (key == GLFW_KEY_W) {
            camera->processKeyboard(FORWARD, deltaTime);
        }
        else if (key == GLFW_KEY_S) {
            camera->processKeyboard(BACKWARD, deltaTime);
        }
        else if (key == GLFW_KEY_A) {
            camera->processKeyboard(LEFT, deltaTime);
        }
        else if (key == GLFW_KEY_D) {
            camera->processKeyboard(RIGHT, deltaTime);
        }
    }

}

void AppController::processMouseMovement(GLFWwindow* window, double xpos, double ypos)
{
    if (lastX == 0.0 && lastY == 0.0) {  
        lastX = xpos;
        lastY = ypos;
    }

    double xOffset = xpos - lastX;
    double yOffset = lastY - ypos;  
    lastX = xpos;
    lastY = ypos;

    camera->processMouseMovement(static_cast<float>(xOffset), static_cast<float>(yOffset));
}

void AppController::processMouseScroll(GLFWwindow* window, double yoffset)
{
    camera->processMouseScroll(static_cast<float>(yoffset));
}

//TRANSFORMATION+
void AppController::applyYRotationToScene(float rotationY)
{
    if (sceneActive) {
        scene.applyRotationToAllObjects(rotationY, 0.0f, 1.0f, 0.0f);
    }
    else {
        scene1.applyRotationToAllObjects(rotationY, 0.0f, 1.0f, 0.0f);
    }
}

void AppController::applyTranslationToScene(Scene& scene, float x, float y) {
    scene.applyTranslationToAllObjects(x, y, 0.0f);
}


void AppController::render() {
    if (sceneActive) {
        scene.render();
    }
    else {
        scene1.render();
    }
}