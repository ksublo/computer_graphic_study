#include "Application.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL

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

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    camera = new Camera(glm::vec3(0.0f, 0.5f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);

    sceneInitializer.setCamera(camera);

    sceneInitializer.initializeScene(scene);
    sceneInitializer.initializeScene1(scene1);
    sceneInitializer.inicializeScene2(scene2);
    sceneInitializer.inicializeScene3(scene3);
    sceneInitializer.inicializeScene4(scene4);

    appController = new AppController(scene, scene1, scene2, scene3, scene4, camera);

    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, Application::keyCallback);
    glfwSetCursorPosCallback(window, mouse_callback); 

    float rotationY = 0.0f;
    float lastFrame = 0.0f;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        float currentFrame = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        sceneInitializer.updateDynamicRotations(deltaTime);

        if (appController->rotationActive) {
            if (rotationY >= 360.0f) {
                rotationY = 0.0f;
            }
            appController->applyYRotationToScene(rotationY);
            rotationY += 0.001f;
        }

        appController->render();
        appController->processInput(window);

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
        app->appController->rotatateY(window, key, scancode, action, mods);
        app->appController->translate(window, key, scancode, action, mods);
        app->appController->cameraWSAD(window, key, scancode, action, mods);
    }
}

void Application::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (app) {
        app->appController->processMouseMovement(window, xpos, ypos);

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !app->mouseClicked) {
            app->mouseClicked = true;  
            app->appController->handleMouseClick(window, xpos, ypos, app->sceneInitializer);
        }

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
            app->mouseClicked = false; 
        }
    }
}


void Application::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);

    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (app && app->camera) {
        app->camera->setResolution(width, height);  
        app->camera->updateProjectionMatrix(static_cast<float>(width) / height);
    }
}



