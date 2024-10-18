#include "SceneInitializer.h"
#include "sphere.h"
#include "gift.h"
#include "shaderList.h"
#include "myTriange.h"
#include "tree.h"
#include "bushes.h"
#include "iostream"

SceneInitializer::SceneInitializer() {
}

SceneInitializer::~SceneInitializer() {
}

void SceneInitializer::initializeScene(Scene& scene) {
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
    transform.translate(0.0f, 0.0f, 0.0f);
    transform.scale(0.2f);
    sphere->setTransformation(transform);

    DrawableObject* gift = new DrawableObject(model2, shaderProgram);
    Transformation transform1;
    transform1.rotate(180.0f, 0.0f, 1.0f, 0.0f);
    transform1.translate(-0.5f, 0.3f, 0.0f);
    transform1.scale(1.f);
    gift->setTransformation(transform1);

    DrawableObject* tri = new DrawableObject(model3, shaderProgram);
    Transformation transform3;
    transform3.rotate(20.0f, 0.0f, 1.0f, 0.0f);
    transform3.rotate(20.0f, 1.0f, 0.0f, 0.0f);
    transform3.translate(-0.5f, -0.5f, 0.0f);
    transform3.scale(0.5f);
    tri->setTransformation(transform3);

    scene.addObject(sphere);
    scene.addObject(gift);
    scene.addObject(tri);
}

void SceneInitializer::initializeScene1(Scene& scene1) {
    Object* model1 = new Object(tree, sizeof(tree), 92814);
    Object* model2 = new Object(bushes, sizeof(bushes), 8730);

    Shader vertexShader(vertex_shader, GL_VERTEX_SHADER);
    vertexShader.compile();

    Shader fragmentShader(fragment_shader, GL_FRAGMENT_SHADER);
    fragmentShader.compile();

    Shader fragmentShader1(fragment_shader_green, GL_FRAGMENT_SHADER);
    fragmentShader1.compile();

    ShaderProgram* shaderProgram = new ShaderProgram(vertexShader, fragmentShader);
    if (!shaderProgram->setShaderProgram()) {
        std::cerr << "Shader program linking failed!" << std::endl;
    }

    ShaderProgram* shaderProgram1 = new ShaderProgram(vertexShader, fragmentShader1);
    if (!shaderProgram1->setShaderProgram()) {
        std::cerr << "Shader program linking failed!" << std::endl;
    }

    shaderProgram->use();
    shaderProgram1->use();

    addTreeObjects(scene1, shaderProgram, model1);
    addBushObjects(scene1, shaderProgram1, model2);
}

void SceneInitializer::addTreeObjects(Scene& scene1, ShaderProgram* shaderProgram, Object* model) {
    float treeX = -0.9f;
    float treeY = -0.4f;
    for (int i = 0; i < 5; ++i) {
        DrawableObject* tree = new DrawableObject(model, shaderProgram);
        Transformation treeTransform;

        float randomRotation = static_cast<float>(rand() % 360);
        float randomScale = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 0.009f + 0.125f;

        treeTransform.translate(treeX, treeY, 0.0f);
        treeTransform.rotate(randomRotation, 0.0f, 1.0f, 0.0f);
        treeTransform.scale(randomScale);
        tree->setTransformation(treeTransform);

        treeX += 0.4f;
        if (i % 2 == 0)
            treeY -= 0.2f;
        else
            treeY += 0.2f;

        scene1.addObject(tree);
    }
}

void SceneInitializer::addBushObjects(Scene& scene1, ShaderProgram* shaderProgram, Object* model) {
    float bushX = -0.9f;
    for (int i = 0; i < 18; ++i) {
        DrawableObject* bush = new DrawableObject(model, shaderProgram);
        Transformation bushTransform;

        float randomY = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 0.3f - 0.7f;
        float randomRotation = static_cast<float>(rand() % 360);
        float randomScale = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 0.3f + 0.25f;

        bushTransform.translate(bushX, randomY, 0.0f);
        bushTransform.rotate(randomRotation, 0.0f, 1.0f, 0.0f);
        bushTransform.scale(randomScale);
        bush->setTransformation(bushTransform);
        bushX += 0.1f;

        scene1.addObject(bush);
    }
}
