#include "Scene.h"
#include "translation.h"
#include "rotation.h"

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
            Rotation* rotation = new Rotation(angle, x, y, z);
            obj->modifyTransformation(rotation); 
        }
    }
}

void Scene::applyTranslationToAllObjects(float x, float y, float z)
{
    for (DrawableObject* obj : objects) {
        if (obj) {
            Translation* translation = new Translation(x, y, z);
            obj->modifyTransformation(translation);  
        }
    }
}



