#pragma once
#include <vector>
#include "DrawableObject.h"

class Scene {
public:
    void addObject(DrawableObject* object);  
    void render();  
    void applyRotationToAllObjects(float angle, float x, float y, float z);
    void applyTranslationToAllObjects(float x, float y, float z);

private:
    std::vector<DrawableObject*> objects;
};

