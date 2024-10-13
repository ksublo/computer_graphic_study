#include "Scene.h"

void Scene::addObject(DrawableObject* object) {
    objects.push_back(object);  
}

void Scene::render() {
    for (auto& object : objects) {
        object->draw();  
    }
}

void Scene::applyRotationToAllObjects(float angle, float x, float y, float z)
{
    for (DrawableObject* obj : objects) {
        if (obj) {
            Transformation currentTransform;  
            currentTransform.rotate(angle, x, y, z);  
            obj->modifyTransformation(currentTransform);  
        }
    }
}

void Scene::applyTranslationToAllObjects(float x, float y, float z)
{
    for (DrawableObject* obj : objects) {
        if (obj) {
            Transformation currentTransform;  
            currentTransform.translate(x, y, z);  
            obj->modifyTransformation(currentTransform);
        }
    }
}
