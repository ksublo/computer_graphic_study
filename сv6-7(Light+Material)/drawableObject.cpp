#include "DrawableObject.h"
#include "ShaderProgram.h"
#include "TransformationGroup.h"

DrawableObject::DrawableObject(Object* object, ShaderProgram* shaderProgram, Material* material)
    : object(object), shaderProgram(shaderProgram), material(material), transformation(nullptr) {
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

    object->bind();
    object->draw();

    glUseProgram(0);
}
