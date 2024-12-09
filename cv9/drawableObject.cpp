#include "DrawableObject.h"
#include "ShaderProgram.h"
#include "TransformationGroup.h"
#include <typeinfo> 

DrawableObject::DrawableObject(Object* object, ShaderProgram* shaderProgram, Material* material)
    : object(object), shaderProgram(shaderProgram), material(material), transformation(nullptr) {

    if (dynamic_cast<TexturedObject*>(object)) {
        hasTexture = true;
    }
    else if (dynamic_cast<ObjectModel*>(object)) {
        hasTexture = true;
    }
    else {
        hasTexture = false; 
    }
    isSkyboxObject = false;
}

void DrawableObject::setTransformation(Transformation* transform) {
    this->transformation = transform;
}

void DrawableObject::modifyTransformation(Transformation* transform) {
    if (transformation) {
        TransformationGroup* group = dynamic_cast<TransformationGroup*>(transformation);
        if (!group) {
            group = new TransformationGroup();
            group->addTransformation(transformation);
            transformation = group;  
        }
        group->addTransformation(transform);  
    }
    else {
        transformation = transform;  
    }
}

void DrawableObject::draw() {
    shaderProgram->use();

    if (material) {
        shaderProgram->setMaterial(*material); 
    }

    if (transformation) {
        glm::mat4 matrix = transformation->getMatrix();
        shaderProgram->setUniformMatrix4fv("modelMatrix", matrix);
    }

    shaderProgram->setUniform("hasTexture", hasTexture);

    if (hasTexture) {
        if (TexturedObject* texturedObject = dynamic_cast<TexturedObject*>(object)) {
            texturedObject->bind();
            int textureUnit = texturedObject->getTextureUnit();
            shaderProgram->setTextureUnit("textureUnit", textureUnit);
        }
        else if (ObjectModel* objectModel = dynamic_cast<ObjectModel*>(object)) {
            objectModel->bind();
            int textureUnit = objectModel->getTextureUnit();
            shaderProgram->setTextureUnit("textureUnit", textureUnit);
        }
    }
    else {
        object->bind();
    }
    object->draw();

    glUseProgram(0);
}

void DrawableObject::setSkybox(bool isSkyboxObject)
{
    this->isSkyboxObject = isSkyboxObject;
}

bool DrawableObject::isSkybox()
{
    return isSkyboxObject;
}


