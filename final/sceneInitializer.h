/**
 *
 * @file sceneInitializer.h
 * @brief Responsible for initializing and configuring various scenes, objects, transformations, etc.
 *
 * @author Kseniia Blokhina
 * @login BLO0021
 *
 */
#pragma once
#include "Scene.h"
#include "Camera.h"
#include "dynamicRotation.h"
#include "objectBase.h"

class SceneInitializer {
public:

    SceneInitializer();
    ~SceneInitializer();

    void initializeScene(Scene& scene);
    void initializeScene1(Scene& scene1);
    void inicializeScene2(Scene& scene2);
    void inicializeScene3(Scene& scene3);
    void inicializeScene4(Scene& scene4);

    void setCamera(Camera* camera);

    void updateDynamicRotations(float deltaTime);

    void addTree(Scene& scene, const glm::vec3& position);

private:

    Camera* camera;
    std::vector<DynamicRotation*> dynamicRotations;

    DrawableObject* createDrawableObjectWithTransform(
        ObjectBase* object ,
        ShaderProgram* shaderProgram,
        Material* material,
        float translationX, float translationY, float translationZ,
        float rotationAngle, float rotationX, float rotationY, float rotationZ,
        float scaleValue
    );

    void addSpheres(Scene& scene, ShaderProgram* shaderProgram, Object* model);
    void addTreeObjects(Scene& scene1, ShaderProgram* shaderProgram, ObjectBase* model, Material* material);
    void addTreeObjectsDefault(Scene& scene1, ShaderProgram* shaderProgram, Object* model, Material* material);
    void addBushObjects(Scene& scene1, ShaderProgram* shaderProgram, Object* model, Material* material);
    void addBushObjectsDefault(Scene& scene1, ShaderProgram* shaderProgram, Object* model, Material* material);
};
