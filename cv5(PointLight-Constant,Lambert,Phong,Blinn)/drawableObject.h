#pragma once
#include "Object.h"
#include "Transformation.h"
#include "ShaderProgram.h"

class DrawableObject {
public:
    DrawableObject(Object* object, ShaderProgram* shaderProgram);

    void setTransformation(Transformation* transform);
    void modifyTransformation(Transformation* transform);
    void draw();

private:
    Object* object;
    Transformation* transformation;  
    ShaderProgram* shaderProgram;
    glm::mat4 viewMatrix;
};
