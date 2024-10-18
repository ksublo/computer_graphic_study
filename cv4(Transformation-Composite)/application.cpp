#include "Application.h"
#include <GLFW/glfw3.h>
#include <iostream>

void Application::run() {
    if (!glfwInit()) {
        return;
    }

    GLFWwindow* window = glfwCreateWindow(1000, 750, "ZPG", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glewInit();

    sceneInitializer.initializeScene(scene);
    sceneInitializer.initializeScene1(scene1);

    glEnable(GL_DEPTH_TEST);

    appController = new AppController(scene, scene1);

    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, Application::keyCallback);


    double rotationY = 0.0f;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (appController->rotationActive) {
            if (rotationY >= 360.0f) {
                rotationY = 0.0f;
            }
            appController->applyYRotationToScene(rotationY);
            rotationY += 0.001f;
        }
        appController->render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete appController;  
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (app) {
        app->appController->switchScene(window, key, scancode, action, mods);
    }
}



