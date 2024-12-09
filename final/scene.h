/**
 *
 * @file scene.h
 * @brief Manages the collection of objects in the scene and handles their rendering
 *
 * @author Kseniia Blokhina
 * @login BLO0021
 *
 */
#pragma once
#include <vector>
#include "DrawableObject.h"
#include "skyboxObject.h"

class Scene {
public:

    void addObject(DrawableObject* object);  
    void render();

    void applyRotationToAllObjects(float angle, float x, float y, float z);
    void applyTranslationToAllObjects(float x, float y, float z);

    void setSkybox(SkyboxObject* skybox); 

private:

    std::vector<DrawableObject*> objects;
    SkyboxObject* skybox = nullptr;
};
