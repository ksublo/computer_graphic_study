#pragma once
#include "sceneInitializer.h"
#include "appController.h"
#include <GLFW/glfw3.h>

class Application {
public:
    void run();
private:
    Camera* camera;
    SceneInitializer sceneInitializer;
    Scene scene;
    Scene scene1;
    Scene scene2;
    Scene scene3;
    Scene scene4;
    AppController* appController; 

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

};
