#pragma once
#include "Scene.h"
#include "Camera.h"

class SceneInitializer {
public:
    SceneInitializer();
    ~SceneInitializer();

    void initializeScene(Scene& scene);
    void initializeScene1(Scene& scene1);
    void inicializeScene2(Scene& scene2);
    void inicializeScene3(Scene& scene3);

    void setCamera(Camera* camera);
    void setLight(Light* light);

private:
    Camera* camera;
    Light* light;

    DrawableObject* createDrawableObjectWithTransform(
        Object* object ,
        ShaderProgram* shaderProgram,
        float translationX, float translationY, float translationZ,
        float rotationAngle, float rotationX, float rotationY, float rotationZ,
        float scaleValue
    );

    void addSpheres(Scene& scene, ShaderProgram* shaderProgram, Object* model);
    void addTreeObjects(Scene& scene1, ShaderProgram* shaderProgram, Object* model);
    void addBushObjects(Scene& scene1, ShaderProgram* shaderProgram, Object* model);

};
