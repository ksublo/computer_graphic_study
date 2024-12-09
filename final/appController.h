/**
 *
 * @file appController.h
 * @brief Handles input processing, scene switching, and rendering control.
 * 
 * @author Kseniia Blokhina
 * @login BLO0021
 *
 */
#pragma once
#include "Scene.h"
#include "sceneInitializer.h"
#include <GLFW/glfw3.h>

class AppController {
public:

    AppController(Scene& scene1, Scene& scene2, Scene& scene3, Scene& scene4, Scene& scene5, Camera* camera);

    //SCENE
    void switchScene(GLFWwindow* window, int key, int scancode, int action, int mods);

    //TRANSFORMATIONS
    void rotatateY(GLFWwindow* window, int key, int scancode, int action, int mods);
    void translate(GLFWwindow* window, int key, int scancode, int action, int mods);

    //CAMERA
    void cameraWSAD(GLFWwindow* window, int key, int scancode, int action, int mods);
    void processMouseMovement(GLFWwindow* window, double xpos, double ypos);

    //TRANSFORMATIONS+
    void applyYRotationToScene(float rotationY);
    void applyTranslationToScene(Scene& scene, float x, float y);

    void render();
    void processInput(GLFWwindow* window);
    void handleMouseClick(GLFWwindow* window, double xpos, double ypos, SceneInitializer& sceneInitializer);
    bool rotationActive = false;

private:

    Scene& scene;      
    Scene& scene1; 
    Scene& scene2;
    Scene& scene3;
    Scene& scene4;
    Camera* camera;
    int sceneActive = 1;
    double lastX = 0.0, lastY = 0.0;
    bool cursorEnabled = false;

    Scene* getActiveScene();

};
