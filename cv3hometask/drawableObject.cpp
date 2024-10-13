#include "DrawableObject.h"
#include "ShaderProgram.h"

DrawableObject::DrawableObject(Object* object, ShaderProgram* shaderProgram)
    : object(object), shaderProgram(shaderProgram) {
}

void DrawableObject::setTransformation(const Transformation& transform) {
    this->transformation = transform;  
}

void DrawableObject::modifyTransformation(const Transformation& transform)
{
    transformation.combine(transform);
}

void DrawableObject::draw() {
    shaderProgram->use();

    transformation.applyTransformation(*shaderProgram, "modelMatrix");

    object->bind();
    object->draw();
}
