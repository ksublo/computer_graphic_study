#include "Application.h"
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

    glfwSetWindowUserPointer(window, this);

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
        if (app)
            app->switchScene(window, key, scancode, action, mods);
        });

    float rotationY = 0.0f;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        

        if (rotationActive) {
            rotationY += 0.00001f;
            if (rotationY >= 360.0f) {
                rotationY = 0.0f;
            }
            applyYRotationToScene(rotationY);
        }
        render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::switchScene(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS && key == GLFW_KEY_S) {
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

void Application::render() {
    if (sceneActive) {
        scene.render();
    }
    else {
        scene1.render();
    }
}

void Application::applyYRotationToScene(float rotationY)
{
    if (sceneActive) {
        scene.applyRotationToAllObjects(rotationY, 0.0f, 1.0f, 0.0f);
    }
    else {
        scene1.applyRotationToAllObjects(rotationY, 0.0f, 1.0f, 0.0f);
    }
}

void Application::applyTranslationToScene(Scene& scene, float x, float y) {
    scene.applyTranslationToAllObjects(x, y, 0.0f);
}
