#include "AppController.h"
#include <iostream>

AppController::AppController(Scene& scene1, Scene& scene2)
    : scene(scene1), scene1(scene2) {}

void AppController::switchScene(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS && key == GLFW_KEY_T) {
        sceneActive = !sceneActive;
        std::cout << "Scene switched!" << std::endl;
    }

    if (action == GLFW_PRESS && key == GLFW_KEY_R) {
        rotationActive = !rotationActive;
        std::cout << "Rotation toggled!" << std::endl;
    }

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