#pragma once
#include "Scene.h"
#include <GLFW/glfw3.h>

class AppController {
public:
    AppController(Scene& scene1, Scene& scene2);

    void switchScene(GLFWwindow* window, int key, int scancode, int action, int mods);
    void applyYRotationToScene(float rotationY);
    void applyTranslationToScene(Scene& scene, float x, float y);

    void render();

    bool rotationActive = false;

private:
    Scene& scene;      
    Scene& scene1;     
    bool sceneActive = true;
};
