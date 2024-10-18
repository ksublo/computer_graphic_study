#pragma once
#include "Scene.h"

class SceneInitializer {
public:
    SceneInitializer();
    ~SceneInitializer();

    void initializeScene(Scene& scene);
    void initializeScene1(Scene& scene1);

private:
    void addTreeObjects(Scene& scene1, ShaderProgram* shaderProgram, Object* model);
    void addBushObjects(Scene& scene1, ShaderProgram* shaderProgram, Object* model);

};
