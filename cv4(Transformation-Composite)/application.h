#pragma once
#include "sceneInitializer.h"
#include "appController.h"
#include <GLFW/glfw3.h>

class Application {
public:
    void run();

private:
    SceneInitializer sceneInitializer;
    Scene scene;
    Scene scene1;
    AppController* appController; 

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};
