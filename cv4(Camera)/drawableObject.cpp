#include "DrawableObject.h"
#include "ShaderProgram.h"
#include "TransformationGroup.h"

DrawableObject::DrawableObject(Object* object, ShaderProgram* shaderProgram)
    : object(object), shaderProgram(shaderProgram), transformation(nullptr), viewMatrix(glm::mat4(1.0f)) {
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

    if (transformation) {
        glm::mat4 matrix = transformation->getMatrix();
        shaderProgram->setUniformMatrix4fv("modelMatrix", matrix);
    }

    object->bind();
    object->draw();
}
