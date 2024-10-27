#include "AppController.h"
#include <iostream>

AppController::AppController(Scene& scene1, Scene& scene2, Scene& scene3, Scene& scene4, Camera* camera)
    : scene(scene1), scene1(scene2), scene2(scene3), scene3(scene4), camera(camera) {}

//SCENE
void AppController::switchScene(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS && key == GLFW_KEY_1) {
        sceneActive = 1;
        std::cout << "Scene switched! Active scene : 1" << std::endl;
    }

    if (action == GLFW_PRESS && key == GLFW_KEY_2) {
        sceneActive = 2;
        std::cout << "Scene switched! Active scene : 2" << std::endl;
    }

    if (action == GLFW_PRESS && key == GLFW_KEY_3) {
        sceneActive = 3;
        std::cout << "Scene switched! Active scene : 3" << std::endl;
    }

    if (action == GLFW_PRESS && key == GLFW_KEY_4) {
        sceneActive = 4;
        std::cout << "Scene switched! Active scene : 4" << std::endl;
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
        Scene* scenes[] = { &scene, &scene1, &scene2, &scene3 };
        Scene* activeScene = (sceneActive >= 1 && sceneActive <= 4)
            ? scenes[sceneActive - 1] 
            : &scene;

        if (key == GLFW_KEY_RIGHT) {
            applyTranslationToScene(*activeScene, translateAmount, 0.0f);
        }
        else if (key == GLFW_KEY_LEFT) {
            applyTranslationToScene(*activeScene, -translateAmount, 0.0f);
        }
        else if (key == GLFW_KEY_UP) {
            applyTranslationToScene(*activeScene, 0.0f, translateAmount);
        }
        else if (key == GLFW_KEY_DOWN) {
            applyTranslationToScene(*activeScene, 0.0f, -translateAmount);
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
    if (sceneActive == 1) {
        scene.applyRotationToAllObjects(rotationY, 0.0f, 1.0f, 0.0f);
    }
    else if (sceneActive == 2) {
        scene1.applyRotationToAllObjects(rotationY, 0.0f, 1.0f, 0.0f);
    }
    else if (sceneActive == 3) {
        scene2.applyRotationToAllObjects(rotationY, 0.0f, 1.0f, 0.0f);
    }
    else {
        scene3.applyRotationToAllObjects(rotationY, 0.0f, 1.0f, 0.0f);
    }
}

void AppController::applyTranslationToScene(Scene& scene, float x, float y) {
    scene.applyTranslationToAllObjects(x, y, 0.0f);
}


void AppController::render() {
    if (sceneActive == 1) {
        scene.render();
    }
    else if (sceneActive == 2) {
        scene1.render();
    }
    else if (sceneActive == 3) {
        scene2.render();
    }
    else {
        scene3.render();
    }
}