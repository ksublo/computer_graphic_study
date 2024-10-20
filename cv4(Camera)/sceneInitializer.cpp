#include "SceneInitializer.h"
#include "transformationGroup.h"
#include "Rotation.h"
#include "Translation.h"
#include "Scale.h"
#include "iostream"

#include "sphere.h"
#include "gift.h"
#include "shaderList.h"
#include "myTriange.h"
#include "tree.h"
#include "bushes.h"

SceneInitializer::SceneInitializer() : camera(nullptr){
}

SceneInitializer::~SceneInitializer() {
}

//SCENE 1
void SceneInitializer::initializeScene(Scene& scene) {
    Object* model1 = new Object(sphere, sizeof(sphere), 2880);
    Object* model2 = new Object(gift, sizeof(gift), 66624);
    Object* model3 = new Object(myTriangle, sizeof(myTriangle), 3);

    Shader vertexShader(vertex_shader_camera, GL_VERTEX_SHADER);
    vertexShader.compile();

    Shader fragmentShader(fragment_shader, GL_FRAGMENT_SHADER);
    fragmentShader.compile();

    ShaderProgram* shaderProgram = new ShaderProgram(vertexShader, fragmentShader);
    if (!shaderProgram->setShaderProgram()) {
        std::cerr << "Shader program linking failed!" << std::endl;
    }

    if (camera == nullptr) {
        std::cerr << "Camera is not initialized!" << std::endl;
        return;
    }
    shaderProgram->setCamera(camera);
    shaderProgram->use();

    // Sphere Transformation
    DrawableObject* sphere = new DrawableObject(model1, shaderProgram);
    Rotation* sphereRotation = new Rotation(0.0f, 0.0f, 1.0f, 0.0f);
    Translation* sphereTranslation = new Translation(0.0f, 0.0f, 0.0f);
    Scale* sphereScale = new Scale(0.2f);

    TransformationGroup* sphereGroup = new TransformationGroup();
    sphereGroup->addTransformation(sphereScale);
    sphereGroup->addTransformation(sphereRotation);
    sphereGroup->addTransformation(sphereTranslation);

    sphere->setTransformation(sphereGroup);

    // Gift Transformation
    DrawableObject* gift = new DrawableObject(model2, shaderProgram);
    Rotation* giftRotation = new Rotation(180.0f, 0.0f, 1.0f, 0.0f);
    Translation* giftTranslation = new Translation(-0.5f, 0.3f, 0.0f);
    Scale* giftScale = new Scale(1.0f);

    TransformationGroup* giftGroup = new TransformationGroup(); 
    giftGroup->addTransformation(giftScale);
    giftGroup->addTransformation(giftRotation);
    giftGroup->addTransformation(giftTranslation);

    gift->setTransformation(giftGroup);  

    // Triangle Transformation
    DrawableObject* tri = new DrawableObject(model3, shaderProgram);
    Rotation* triRotation = new Rotation(20.0f, 0.0f, 1.0f, 0.0f);
    Translation* triTranslation = new Translation(-0.8f, -0.7f, 0.0f);
    Scale* triScale = new Scale(0.5f);

    TransformationGroup* triGroup = new TransformationGroup();
    triGroup->addTransformation(triScale);
    triGroup->addTransformation(triRotation);
    triGroup->addTransformation(triTranslation);

    tri->setTransformation(triGroup); 

    scene.addObject(sphere);
    scene.addObject(gift);
    scene.addObject(tri);
}

//SCENE 2
void SceneInitializer::initializeScene1(Scene& scene1) {
    Object* model1 = new Object(tree, sizeof(tree), 92814);
    Object* model2 = new Object(bushes, sizeof(bushes), 8730);

    Shader vertexShader(vertex_shader_camera, GL_VERTEX_SHADER);
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

    if (camera == nullptr) {
        std::cerr << "Camera is not initialized!" << std::endl;
        return;
    }
    shaderProgram->setCamera(camera);
    shaderProgram1->setCamera(camera);

    shaderProgram->use();
    shaderProgram1->use();

    addTreeObjects(scene1, shaderProgram, model1);
    addBushObjects(scene1, shaderProgram1, model2);
}

void SceneInitializer::setCamera(Camera* camera)
{
    this->camera = camera;
}

void SceneInitializer::addTreeObjects(Scene& scene1, ShaderProgram* shaderProgram, Object* model) {
  
    for (int i = 0; i < 100; ++i) {
        DrawableObject* tree = new DrawableObject(model, shaderProgram);

        float treeX = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 10.0f - 5.0f;
        float treeY = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 0.1f;
        float treeZ = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 10.0f - 5.0f;
        float randomRotation = static_cast<float>(rand() % 360);
        float randomScale = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 0.009f + 0.125f;

        Translation* treeTranslation = new Translation(treeX, treeY, treeZ);
        Rotation* treeRotation = new Rotation(randomRotation, 0.0f, 1.0f, 0.0f);
        Scale* treeScale = new Scale(randomScale);

        TransformationGroup* treeGroup = new TransformationGroup();
        treeGroup->addTransformation(treeScale);
        treeGroup->addTransformation(treeRotation);
        treeGroup->addTransformation(treeTranslation);

        tree->setTransformation(treeGroup); 
        scene1.addObject(tree);
    }
}

void SceneInitializer::addBushObjects(Scene& scene1, ShaderProgram* shaderProgram, Object* model) {
    for (int i = 0; i < 150; ++i) {
        DrawableObject* bush = new DrawableObject(model, shaderProgram);

        float bushX = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 10.0f - 5.0f;
        float bushY = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 0.095f;
        float bushZ = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 10.0f - 5.0f;

        float randomRotation = static_cast<float>(rand() % 360);
        float randomScale = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 0.1f + 0.5f;

        Translation* bushTranslation = new Translation(bushX, bushY, bushZ);
        Rotation* bushRotation = new Rotation(randomRotation, 0.0f, 1.0f, 0.0f);
        Scale* bushScale = new Scale(randomScale);

        TransformationGroup* bushGroup = new TransformationGroup();
        bushGroup->addTransformation(bushScale);
        bushGroup->addTransformation(bushRotation);
        bushGroup->addTransformation(bushTranslation);

        bush->setTransformation(bushGroup);  
        scene1.addObject(bush);
    }
}

