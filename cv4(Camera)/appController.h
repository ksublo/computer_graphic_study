#pragma once
#include "Scene.h"
#include <GLFW/glfw3.h>

class AppController {
public:
    AppController(Scene& scene1, Scene& scene2, Camera* camera);

    //SCENE
    void switchScene(GLFWwindow* window, int key, int scancode, int action, int mods);

    //TRANSFORMATIONS
    void rotatateY(GLFWwindow* window, int key, int scancode, int action, int mods);
    void translate(GLFWwindow* window, int key, int scancode, int action, int mods);

    //CAMERA
    void cameraWSAD(GLFWwindow* window, int key, int scancode, int action, int mods);
    void processMouseMovement(GLFWwindow* window, double xpos, double ypos);
    void processMouseScroll(GLFWwindow* window, double yoffset);

    //TRANSFORMATIONS+
    void applyYRotationToScene(float rotationY);
    void applyTranslationToScene(Scene& scene, float x, float y);

    void render();

    bool rotationActive = false;

private:
    Scene& scene;      
    Scene& scene1; 
    Camera* camera;
    bool sceneActive = true;
    double lastX = 0.0, lastY = 0.0;
};