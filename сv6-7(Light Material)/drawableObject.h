#pragma once
#include "Object.h"
#include "Transformation.h"
#include "ShaderProgram.h"
#include "Material.h"

class DrawableObject {
public:
    DrawableObject(Object* object, ShaderProgram* shaderProgram, Material* material);

    void setTransformation(Transformation* transform);
    void modifyTransformation(Transformation* transform);
    void draw();

private:
    Object* object;
    Transformation* transformation;  
    ShaderProgram* shaderProgram;
    Material* material;
};
