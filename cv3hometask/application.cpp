#include "Application.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "sphere.h"
#include "gift.h"
#include "shaderList.h"
#include "myTriange.h"
#include "tree.h"
#include "bushes.h"
#include "iostream"


void Application::initScene() {
  
    Object* model1 = new Object(sphere, sizeof(sphere), 2880);
    Object* model2 = new Object(gift, sizeof(gift), 66624);
    Object* model3 = new Object(myTriangle, sizeof(myTriangle), 3);

    Shader vertexShader(vertex_shader, GL_VERTEX_SHADER);  
    vertexShader.compile();

    Shader fragmentShader(fragment_shader, GL_FRAGMENT_SHADER);  
    fragmentShader.compile();

    ShaderProgram* shaderProgram = new ShaderProgram(vertexShader, fragmentShader);
    if (!shaderProgram->setShaderProgram()) {
        std::cerr << "Shader program linking failed!" << std::endl;
    }

    shaderProgram->use();

    DrawableObject* sphere = new DrawableObject(model1, shaderProgram);
    Transformation transform;
    transform.rotate(0.0f, 0.0f, 1.0f, 0.0f);
    transform.translate(0.0f, 0.0f, 0.5f);  
    transform.scale(0.2f);
    sphere->setTransformation(transform);

    DrawableObject* gift = new DrawableObject(model2, shaderProgram);
    Transformation transform1;
    transform1.rotate(180.0f, 0.0f, 1.0f, 0.0f);
    transform1.translate(-0.5f ,0.3f, 0.5f);
    transform1.scale(1.f);
    gift->setTransformation(transform1);

    DrawableObject* tri = new DrawableObject(model3, shaderProgram);
    Transformation transform3;
    transform3.rotate(20.0f, 0.0f, 1.0f, 0.0f);
    transform3.rotate(20.0f, 1.0f, 0.0f, 0.0f);
    transform3.translate(-0.5f, -0.5f, 0.5f);
    transform3.scale(0.5f);
    tri->setTransformation(transform3);


    scene.addObject(sphere);
    scene.addObject(gift);
    scene.addObject(tri);
}

void Application::initScene1()
{
    Object* model1 = new Object(tree, sizeof(tree), 92814);
    Object* model2 = new Object(bushes, sizeof(bushes), 8730);

    Shader vertexShader(vertex_shader, GL_VERTEX_SHADER);
    vertexShader.compile();

    Shader fragmentShader(fragment_shader, GL_FRAGMENT_SHADER);
    fragmentShader.compile();

    ShaderProgram* shaderProgram = new ShaderProgram(vertexShader, fragmentShader);
    if (!shaderProgram->setShaderProgram()) {
        std::cerr << "Shader program linking failed!" << std::endl;
    }

    shaderProgram->use();

    for (int i = 0; i < 4; ++i) {  
        DrawableObject* tree = new DrawableObject(model1, shaderProgram);

        Transformation treeTransform;
        float randomX = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0f - 1.0f;
        float randomY = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0f - 1.5f;
        float randomZ = 0.5f;

        float randomRotation = static_cast<float>(rand() % 360);

        float randomScale = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (0.175f - 0.05f) + 0.05f;

        treeTransform.translate(randomX, randomY, randomZ);
        treeTransform.rotate(randomRotation, 0.0f, 1.0f, 0.0f);
        treeTransform.scale(randomScale);
        tree->setTransformation(treeTransform);

        scene1.addObject(tree);  
    }

    for (int i = 0; i < 10; ++i) {  
        DrawableObject* bush = new DrawableObject(model2, shaderProgram);

        Transformation bushTransform;
        float randomX = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0f - 1.0f;
        float randomY = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0f - 1.5f;
        float randomZ = 0.5f;

        float randomRotation = static_cast<float>(rand() % 360);

        float randomScale = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 0.5f;

        bushTransform.translate(randomX, randomY, randomZ);
        bushTransform.rotate(randomRotation, 0.0f, 1.0f, 0.0f);
        bushTransform.scale(randomScale);
        bush->setTransformation(bushTransform);

        scene1.addObject(bush);  
    }
 
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

void Application::run() {

    if (!glfwInit()) {
        return;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "ZPG", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glewInit();

    initScene();
    initScene1();

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
            rotationY += 0.000001f;  
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
