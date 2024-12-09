#include "Scene.h"
#include "translation.h"
#include "rotation.h"

void Scene::addObject(DrawableObject* object) {
    objects.push_back(object);  
}

void Scene::render() {

    glDepthMask(GL_FALSE);

    for (auto& object : objects) {
        if (object->isSkybox()) {
            object->draw();
        }
    }

    glDepthMask(GL_TRUE);

    for (auto& object : objects) {
        if (!object->isSkybox()) {
            object->draw();
        }
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

void Scene::setSkybox(SkyboxObject* skyboxObj)
{
    this->skybox = skyboxObj;
}





