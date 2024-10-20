#pragma once
#include "Scene.h"
#include "Camera.h"

class SceneInitializer {
public:
    SceneInitializer();
    ~SceneInitializer();

    void initializeScene(Scene& scene);
    void initializeScene1(Scene& scene1);

    void setCamera(Camera* camera);

private:
    Camera* camera;
    void addTreeObjects(Scene& scene1, ShaderProgram* shaderProgram, Object* model);
    void addBushObjects(Scene& scene1, ShaderProgram* shaderProgram, Object* model);

};
