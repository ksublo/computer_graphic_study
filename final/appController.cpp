#include "AppController.h"
#include <iostream>

AppController::AppController(Scene& scene1, Scene& scene2, Scene& scene3, Scene& scene4, Scene& scene5, Camera* camera)
    : scene(scene1), scene1(scene2), scene2(scene3), scene3(scene4), scene4(scene5), camera(camera) {}

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

    if (action == GLFW_PRESS && key == GLFW_KEY_5) {
        sceneActive = 5;
        std::cout << "Scene switched! Active scene : 5" << std::endl;
    }

    if (action == GLFW_PRESS && key == GLFW_KEY_T) {
        camera->resetPosition(glm::vec3(0.0f, 0.5f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        std::cout << "Camera position reset" << std::endl;
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
        Scene* activeScene = getActiveScene();

        if (activeScene) {
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
    if (cursorEnabled) {
        return;
    }

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

//TRANSFORMATION+
void AppController::applyYRotationToScene(float rotationY)
{
    Scene* activeScene = getActiveScene();
    if (activeScene) {
        activeScene->applyRotationToAllObjects(rotationY, 0.0f, 1.0f, 0.0f);
    }
}

void AppController::applyTranslationToScene(Scene& scene, float x, float y) {
    scene.applyTranslationToAllObjects(x, y, 0.0f);
}


void AppController::render() {
    Scene* activeScene = getActiveScene();
    if (activeScene) {
        activeScene->render();  
    }
}

void AppController::processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); 
        cursorEnabled = true;
    }
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 
        cursorEnabled = false;
    }
}

void AppController::handleMouseClick(GLFWwindow* window, double xpos, double ypos, SceneInitializer& sceneInitializer) {
    GLint x = static_cast<GLint>(xpos);
    GLint y = static_cast<GLint>(ypos);

    GLint newy = camera->getResolution().y - y;

    GLbyte color[4];
    GLfloat depth;
    GLuint index;

    glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
    glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
    glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

    printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index %u\n",
        x, newy, color[0], color[1], color[2], color[3], depth, index);

    if (depth <= 0.0f || std::isnan(depth)) {
        printf("Invalid depth value at (%d, %d): %f\n", x, y, depth);
        return;
    }

    glm::vec3 screenPos = glm::vec3(x, newy, depth);
    glm::mat4 view = camera->getViewMatrix();
    glm::mat4 projection = camera->getProjectionMatrix();
    glm::vec4 viewport = glm::vec4(0, 0, camera->getResolution().x, camera->getResolution().y);

    glm::vec3 worldPos = glm::unProject(screenPos, view, projection, viewport);

    printf("Unprojected World Position: [%f, %f, %f]\n", worldPos.x, worldPos.y, worldPos.z);

  
        Scene* activeScene = getActiveScene();
        if (activeScene) {
            sceneInitializer.addTree(*activeScene, worldPos);
            printf("Tree added at [%f, %f, %f]\n", worldPos.x, worldPos.y, worldPos.z);
        }
}

Scene* AppController::getActiveScene()
{
    Scene* scenes[] = { &scene, &scene1, &scene2, &scene3, &scene4 };
    if (sceneActive >= 1 && sceneActive <= 5) {
        return scenes[sceneActive - 1];
    }
    return nullptr;
}

