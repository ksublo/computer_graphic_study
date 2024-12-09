#include "SceneInitializer.h"
#include "transformationGroup.h"
#include "Rotation.h"
#include "dynamicRotation.h"
#include "Translation.h"
#include "Scale.h"
#include "shaderLoader.h"
#include "material.h"
#include "skyboxObject.h"
#include "texturedObject.h"
#include "objectModel.h"

#include "iostream"
#include <vector>
#include <ctime>

#include "sphere.h"
#include "gift.h"
#include "shaderList.h"
#include "myTriange.h"
#include "tree.h"
#include "bushes.h"
#include "plain.h"
#include "suzi_flat.h"
#include "suzi_smooth.h"
#include "plainTex.h"
#include "skycube.h"

using namespace std;

SceneInitializer::SceneInitializer() : camera(nullptr) {
}

SceneInitializer::~SceneInitializer() {
}

//SCENE 1
void SceneInitializer::initializeScene(Scene& scene) {

    //Materials
    Material* defaultMaterial = new Material(
        glm::vec3(0.2f, 0.2f, 0.2f),
        glm::vec3(0.8f, 0.8f, 0.8f),
        glm::vec3(0.1f, 0.1f, 0.1f),
        8.0f
    );

    //Objects
    Object* model1 = new Object(myTriangle, sizeof(myTriangle), 3);

    //Shaders
    const char* vertexFile = "vertex_shader_camera.glsl";
    const char* fragmentFile = "fragment_shader.glsl";
    ShaderProgram* shaderProgram = new ShaderProgram(vertexFile, fragmentFile);

    shaderProgram->setCamera(camera);

    //Drawable Objects
    DrawableObject* triangle = createDrawableObjectWithTransform(
        model1,
        shaderProgram,
        defaultMaterial,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        2.0f
    );
    scene.addObject(triangle);
}

//SCENE 2
void SceneInitializer::initializeScene1(Scene& scene1) {

    //Materials
    Material* forestMaterial = new Material(
        glm::vec3(0.1f, 0.1f, 0.1f),
        glm::vec3(0.7f, 0.7f, 0.7f),
        glm::vec3(2.0f, 2.0f, 2.0f),
        25.0f
    );

    //Textures
    Texture* grassTex = new Texture("negy.jpg", 1);
    Texture* loginTex = new Texture("posy.jpg", 6);

    //Objects/Models
    Object* model1 = new Object(tree, sizeof(tree), 92814);
    Object* model2 = new Object(bushes, sizeof(bushes), 8730);
    TexturedObject* grassModel = new TexturedObject(plainTex, sizeof(plainTex), 6);
    SkyboxObject* skybox = new SkyboxObject(skycube, sizeof(skycube), 36);
    ObjectModel* login = new ObjectModel("untitled.obj");

    //Shaders
    ShaderProgram* shaderProgram = new ShaderProgram("vertex_shader_light.glsl", "fragment_shader_phong.glsl");
    ShaderProgram* shaderProgramTextured = new ShaderProgram("vertex_shader_light.glsl", "fragment_shader_phong_textured.glsl");
    ShaderProgram* shaderProgramObj = new ShaderProgram("vertex_shader_object_model_light.glsl", "fragment_shader_object_model_phong.glsl");
    shaderProgram->setCamera(camera);
    shaderProgramTextured->setCamera(camera);
    shaderProgramObj->setCamera(camera);

    DrawableObject* plain = createDrawableObjectWithTransform(
        grassModel,
        shaderProgramTextured,
        forestMaterial,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        5.0f
    );
    plain->setTexture(grassTex);
    scene1.addObject(plain);

    DrawableObject* loginDO = createDrawableObjectWithTransform(
        login,
        shaderProgramObj,
        forestMaterial,
        -3.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        2.0f
    );
    loginDO->setTexture(loginTex);
    scene1.addObject(loginDO);

    addTreeObjectsDefault(scene1, shaderProgram, model1, forestMaterial);
    addBushObjectsDefault(scene1, shaderProgram, model2, forestMaterial);

    //Lights
    std::vector<Light>* lights = new std::vector<Light>();
    lights->emplace_back(LightType::POINT,
        glm::vec3(-3.0f, 0.5f, -3.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        1.0f,
        1.0f,
        1.0f,
        2.0f
    );
    lights->emplace_back(LightType::POINT,
        glm::vec3(3.0f, 0.5f, 3.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        1.0f,
        1.0f,
        1.0f,
        2.0f
    );
    lights->emplace_back(LightType::POINT,
        glm::vec3(-3.0f, 0.5f, 3.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        1.0f,
        1.0f,
        1.0f,
        2.0f
    );
    lights->emplace_back(LightType::POINT,
        glm::vec3(3.0f, 0.5f, -3.0f),
        glm::vec3(1.0f, 1.0f, 0.0f),
        1.0f,
        1.0f,
        1.0f,
        2.0f
    );
    lights->emplace_back(
        LightType::DIRECTIONAL,
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.5f, 0.0f, 0.7f),
        2.0f
    );
    lights->emplace_back(LightType::SPOT,
        camera->getPosition(),
        camera->getForward(),
        glm::vec3(1.0f, 1.0f, 1.0f),
        3.0f,
        1.0f,
        0.1f,
        0.05f,
        glm::cos(glm::radians(3.0f))
    );
    
    shaderProgram->setLights(lights);
    shaderProgram->update();
    shaderProgramTextured->setLights(lights);
    shaderProgramTextured->update();
    shaderProgramObj->setLights(lights);
    shaderProgramObj->update();

}


//SCENE 3
void SceneInitializer::inicializeScene2(Scene& scene2)
{
    //Objects
    Object* model1 = new Object(sphere, sizeof(sphere), 2880);

    //Shaders
    const char* vertexFile = "vertex_shader_light.glsl";
    const char* fragmentFile = "fragment_shader_phong.glsl";
    ShaderProgram* shaderProgram = new ShaderProgram(vertexFile, fragmentFile);
    shaderProgram->setCamera(camera);

    //Lights
    std::vector<Light>* lights = new std::vector<Light>();
    lights->emplace_back(LightType::POINT,
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.5f, 0.5f, 1.0f),
        1.0f,
        1.0f,
        0.1f,
        0.1f
    );

    shaderProgram->setLights(lights);

    //DrawableObjects & Scene
    addSpheres(scene2, shaderProgram, model1);
}

//SCENE 4
void SceneInitializer::inicializeScene3(Scene& scene3)
{
    //Materials
    Material* defaultMaterial = new Material(
        glm::vec3(0.25f, 0.25f, 0.25f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(3.0f, 3.0f, 3.0f),
        20.0f
    );

    //Objects
    Object* suziF = new Object(suziFlat, sizeof(suziFlat), 2904);
    Object* suziS = new Object(suziSmooth, sizeof(suziSmooth), 2904);
    Object* spheree = new Object(sphere, sizeof(sphere), 2880);

    //Shaders
    const char* vertexFileLight = "vertex_shader_light.glsl";
    const char* fragmentFileConstant = "fragment_shader_constant.glsl";
    const char* fragmentFileLambert = "fragment_shader_lambert.glsl";
    const char* fragmentFilePhong = "fragment_shader_phong.glsl";
    const char* fragmentFileBlinn = "fragment_shader_blinn.glsl";

    ShaderProgram* shaderProgramConstant = new ShaderProgram(vertexFileLight, fragmentFileConstant);
    ShaderProgram* shaderProgramLambert = new ShaderProgram(vertexFileLight, fragmentFileLambert);
    ShaderProgram* shaderProgramPhong = new ShaderProgram(vertexFileLight, fragmentFilePhong);
    ShaderProgram* shaderProgramBlinn = new ShaderProgram(vertexFileLight, fragmentFileBlinn);

    shaderProgramConstant->setCamera(camera);
    shaderProgramLambert->setCamera(camera);
    shaderProgramPhong->setCamera(camera);
    shaderProgramBlinn->setCamera(camera);

    //DrawableObjects & Scene
    // SuziFlat
    DrawableObject* objSuziFlatConstant = createDrawableObjectWithTransform(
        suziF,
        shaderProgramConstant,
        defaultMaterial,
        -5.0f, 5.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        1.0f
    );
    scene3.addObject(objSuziFlatConstant);

    DrawableObject* objSuziFlatLambert = createDrawableObjectWithTransform(
        suziF,
        shaderProgramLambert,
        defaultMaterial,
        -2.0f, 5.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        1.0f
    );
    scene3.addObject(objSuziFlatLambert);

    DrawableObject* objSuziFlatPhong = createDrawableObjectWithTransform(
        suziF,
        shaderProgramPhong,
        defaultMaterial,
        1.0f, 5.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        1.0f
    );
    scene3.addObject(objSuziFlatPhong);

    DrawableObject* objSuziFlatBlinn = createDrawableObjectWithTransform(
        suziF,
        shaderProgramBlinn,
        defaultMaterial,
        4.0f, 5.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        1.0f
    );
    scene3.addObject(objSuziFlatBlinn);

    // SuziSmooth
    DrawableObject* objSuziSmoothConstant = createDrawableObjectWithTransform(
        suziF,
        shaderProgramConstant,
        defaultMaterial,
        -5.0f, 2.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        1.0f
    );
    scene3.addObject(objSuziSmoothConstant);

    DrawableObject* objSuziSmoothLambert = createDrawableObjectWithTransform(
        suziS,
        shaderProgramLambert,
        defaultMaterial,
        -2.0f, 2.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        1.0f
    );
    scene3.addObject(objSuziSmoothLambert);

    DrawableObject* objSuziSmoothPhong = createDrawableObjectWithTransform(
        suziS,
        shaderProgramPhong,
        defaultMaterial,
        1.0f, 2.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        1.0f
    );
    scene3.addObject(objSuziSmoothPhong);

    DrawableObject* objSuziSmoothBlinn = createDrawableObjectWithTransform(
        suziS,
        shaderProgramBlinn,
        defaultMaterial,
        4.0f, 2.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        1.0f
    );
    scene3.addObject(objSuziSmoothBlinn);

    // Sphere
    DrawableObject* objSphereConstant = createDrawableObjectWithTransform(
        spheree,
        shaderProgramConstant,
        defaultMaterial,
        -5.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        1.0f
    );
    scene3.addObject(objSphereConstant);

    DrawableObject* objSphereLambert = createDrawableObjectWithTransform(
        spheree,
        shaderProgramLambert,
        defaultMaterial,
        -2.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        1.0f
    );
    scene3.addObject(objSphereLambert);

    DrawableObject* objSpherePhong = createDrawableObjectWithTransform(
        spheree,
        shaderProgramPhong,
        defaultMaterial,
        1.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        1.0f
    );
    scene3.addObject(objSpherePhong);

    DrawableObject* objSphereBlinn = createDrawableObjectWithTransform(
        spheree,
        shaderProgramBlinn,
        defaultMaterial,
        4.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        1.0f
    );
    scene3.addObject(objSphereBlinn);

    //Lights
    std::vector<Light>* lights = new std::vector<Light>();
    lights->emplace_back(LightType::POINT,
        glm::vec3(-0.5f, 2.0f, 5.0f),
        glm::vec3(0.5f, 0.5f, 1.0f),
        1.0f,
        1.0f,
        0.001f,
        0.001f
    );

    shaderProgramConstant->setLights(lights);
    shaderProgramLambert->setLights(lights);
    shaderProgramPhong->setLights(lights);
    shaderProgramBlinn->setLights(lights);
}

//SCENE 5
void SceneInitializer::inicializeScene4(Scene& scene4)
{
    //Materials
    Material* forestMaterial = new Material(
        glm::vec3(0.1f, 0.1f, 0.1f),
        glm::vec3(0.7f, 0.7f, 0.7f),
        glm::vec3(2.0f, 2.0f, 2.0f),
        25.0f
    );

    //Textures
    Texture* grassTex = new Texture("negy.jpg", 1);
    Texture* skyboxTex = new Texture("posx.jpg", "negx.jpg", "posy.jpg", "negy.jpg", "posz.jpg", "negz.jpg", 0);
    Texture* houseTex = new Texture("house.png", 2);
    Texture* loginTex = new Texture("login.jpg", 3);
    Texture* conteinerTex = new Texture("Container.jpg", 4);
    Texture* skullTex = new Texture("Skull.jpg", 5);
    Texture* treeTex = new Texture("tree.png", 7);

    //Objects(Models)
    Object* model1 = new Object(tree, sizeof(tree), 92814);
    Object* model2 = new Object(bushes, sizeof(bushes), 8730);
    TexturedObject* grassModel = new TexturedObject(plainTex, sizeof(plainTex), 6);
    SkyboxObject* skybox = new SkyboxObject(skycube, sizeof(skycube), 36);
    ObjectModel* house = new ObjectModel("house.obj");
    ObjectModel* login = new ObjectModel("untitled.obj");
    ObjectModel* skull = new ObjectModel("12140_Skull_v3_L2.obj");
    ObjectModel* container = new ObjectModel("Container.obj");
    ObjectModel* tree = new ObjectModel("tree.obj");

    //Shaders
    ShaderProgram* shaderProgram = new ShaderProgram("vertex_shader_camera.glsl", "fragment_shader.glsl");
    ShaderProgram* shaderProgramSkybox = new ShaderProgram("vertex_shader_skybox.glsl", "fragment_shader_skybox.glsl");
    ShaderProgram* shaderProgramTexturedObj = new ShaderProgram("vertex_shader_camera.glsl", "fragment_shader_texture.glsl");
    ShaderProgram* shaderProgramObj = new ShaderProgram("vertex_shader_object_model.glsl", "fragment_shader_object_model.glsl");

    shaderProgram->setCamera(camera);
    shaderProgramSkybox->setCamera(camera);
    shaderProgramTexturedObj->setCamera(camera);
    shaderProgramObj->setCamera(camera);

    //Drawable Objects & Scene
    DrawableObject* plain = createDrawableObjectWithTransform(
        grassModel,
        shaderProgramTexturedObj,
        forestMaterial,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        10.0f
    );
    plain->setTexture(grassTex);
    scene4.addObject(plain);

    DrawableObject* houseDO = createDrawableObjectWithTransform(
        house,
        shaderProgramObj,
        forestMaterial,
        1.5f, 0.0f, 3.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.2f
    );
    houseDO->setTexture(houseTex);
    scene4.addObject(houseDO);

    DrawableObject* loginDO = createDrawableObjectWithTransform(
        login,
        shaderProgramObj,
        forestMaterial,
        -7.0f, 0.0f, 5.0f,
        90.0f, 0.0f, 1.0f, 0.0f,
        1.0f
    );
    loginDO->setTexture(loginTex);
    scene4.addObject(loginDO);

    DrawableObject* containerDO = createDrawableObjectWithTransform(
        container,
        shaderProgramObj,
        forestMaterial,
        0.0f, 0.0f, -2.0f,
        15.0f, 0.0f, 1.0f, 0.0f,
        0.003f
     );
    containerDO->setTexture(conteinerTex);
    scene4.addObject(containerDO);
  

    DrawableObject* box = new DrawableObject(skybox, shaderProgramSkybox, nullptr);
    box->setTexture(skyboxTex);
    box->setSkybox(true);
    scene4.addObject(box);
    scene4.setSkybox(skybox);

    addTreeObjects(scene4, shaderProgramObj, tree, forestMaterial);
    addBushObjects(scene4, shaderProgram, model2, forestMaterial);

}

void SceneInitializer::setCamera(Camera* camera)
{
    this->camera = camera;
}

DrawableObject* SceneInitializer::createDrawableObjectWithTransform(ObjectBase* object, ShaderProgram* shaderProgram, Material* material, float translationX, float translationY, float translationZ, float rotationAngle, float rotationX, float rotationY, float rotationZ, float scaleValue)
{
    DrawableObject* drawableObject = new DrawableObject(object, shaderProgram, material);

    Translation* translation = new Translation(translationX, translationY, translationZ);
    Rotation* rotation = new Rotation(rotationAngle, rotationX, rotationY, rotationZ);
    Scale* scale = new Scale(scaleValue);

    TransformationGroup* transformGroup = new TransformationGroup();
    transformGroup->addTransformation(scale);
    transformGroup->addTransformation(rotation);
    transformGroup->addTransformation(translation);
    

    drawableObject->setTransformation(transformGroup);

    return drawableObject;
}

void SceneInitializer::addSpheres(Scene& scene, ShaderProgram* shaderProgram, Object* model)
{
    Material* sphereMaterial = new Material(
        glm::vec3(0.25f, 0.25f, 0.25f), 
        glm::vec3(1.0f, 1.0f, 1.0f),   
        glm::vec3(5.0f, 5.0f, 5.0f), 
        20.0f                         
    );

    vector<glm::vec3> positions = {
        {0.0f, 2.0f, 0.0f},
        {2.0f, 0.0f, 0.0f},
        {0.0f, -2.0f, 0.0f},
        {-2.0f, 0.0f, 0.0f}
    };

    for (const auto& pos : positions) {
        DrawableObject* obj = createDrawableObjectWithTransform(
            model,
            shaderProgram,
            sphereMaterial,
            pos.x, pos.y, pos.z,
            0.0f, 0.0f, 1.0f, 0.0f,
            1.0f
        );
        scene.addObject(obj);
    }
}

void SceneInitializer::addTreeObjects(Scene& scene1, ShaderProgram* shaderProgram, ObjectBase* model, Material* material) {
  
    int i;
    for (i = 0; i < 70; ++i) {
        DrawableObject* tree = new DrawableObject(model, shaderProgram, material);

        float treeX = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 20.0f - 10.0f;
        float treeZ = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 20.0f - 10.0f;
        float randomRotation = static_cast<float>(rand() % 360);
        float randomScale = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 0.05f + 0.02f;

        Translation* treeTranslation = new Translation(treeX, 0.0f, treeZ);
        Rotation* treeRotation = new Rotation(randomRotation, 0.0f, 1.0f, 0.0f);
        Scale* treeScale = new Scale(randomScale);

        TransformationGroup* treeGroup = new TransformationGroup();
        treeGroup->addTransformation(treeScale);
        treeGroup->addTransformation(treeRotation);

        if (i % 5 == 0) {  
            float rotationSpeed = static_cast<float>(rand() % 21 + 50);
            DynamicRotation* dynamicRotation = new DynamicRotation(rotationSpeed, 0.0f, 1.0f, 0.0f);
            treeGroup->addTransformation(dynamicRotation);
            dynamicRotations.push_back(dynamicRotation);  
        }

        treeGroup->addTransformation(treeTranslation);

        tree->setTransformation(treeGroup); 
        Texture* treeTex = new Texture("tree.png", 7);
        tree->setTexture(treeTex);
        scene1.addObject(tree);
    }

}

void SceneInitializer::addTreeObjectsDefault(Scene& scene1, ShaderProgram* shaderProgram, Object* model, Material* material) {

    int i;
    for (i = 0; i < 70; ++i) {
        DrawableObject* tree = new DrawableObject(model, shaderProgram, material);
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
        if (i % 5 == 0) {
            float rotationSpeed = static_cast<float>(rand() % 21 + 50);
            DynamicRotation* dynamicRotation = new DynamicRotation(rotationSpeed, 0.0f, 1.0f, 0.0f);
            treeGroup->addTransformation(dynamicRotation);
            dynamicRotations.push_back(dynamicRotation);
        }
        treeGroup->addTransformation(treeTranslation);
        tree->setTransformation(treeGroup);
        scene1.addObject(tree);
    }
}

void SceneInitializer::addBushObjects(Scene& scene1, ShaderProgram* shaderProgram, Object* model, Material* material) {
    for (int i = 0; i < 1000; ++i) {
        DrawableObject* bush = new DrawableObject(model, shaderProgram, material);

        float bushX = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 20.0f - 10.0f;
        float bushZ = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 20.0f - 10.0f;

        float randomRotation = static_cast<float>(rand() % 360);
        float randomScale = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 0.1f + 0.1f;

        Translation* bushTranslation = new Translation(bushX, 0.0f, bushZ);
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

void SceneInitializer::addBushObjectsDefault(Scene& scene1, ShaderProgram* shaderProgram, Object* model, Material* material) {
    for (int i = 0; i < 1000; ++i) {
        DrawableObject* bush = new DrawableObject(model, shaderProgram, material);

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

void SceneInitializer::updateDynamicRotations(float deltaTime) {
    for (DynamicRotation* dynamicRotation : dynamicRotations) {
        dynamicRotation->update(deltaTime);  
    }
}

void SceneInitializer::addTree(Scene& scene, const glm::vec3& position) {
 
    Object* tree1 = new Object(tree, sizeof(tree), 92814);

    ShaderProgram* shaderProgramObj1 = new ShaderProgram("vertex_shader_camera.glsl", "fragment_shader.glsl");
    shaderProgramObj1->setCamera(camera);

    DrawableObject* treeDO = createDrawableObjectWithTransform(
        tree1,
        shaderProgramObj1,
        nullptr,
        position.x, position.y, position.z,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.3f
    );
    scene.addObject(treeDO);

    printf("Tree planted at [%f, %f, %f]\n", position.x, position.y, position.z);
}
