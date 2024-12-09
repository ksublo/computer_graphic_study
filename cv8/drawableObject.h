#pragma once
#include "Object.h"
#include "TexturedObject.h"
#include "skyboxObject.h"
#include "Transformation.h"
#include "ShaderProgram.h"
#include "Material.h"

class DrawableObject {
public:
    DrawableObject(Object* object, ShaderProgram* shaderProgram, Material* material);

    void setTransformation(Transformation* transform);
    void modifyTransformation(Transformation* transform);
    void draw();

    void setSkybox(bool isSkyboxObject);
    bool isSkybox();

    void setTexture(bool hasTexture);
    bool isTextured();

private:
    Object* object;
    Transformation* transformation;  
    ShaderProgram* shaderProgram;
    Material* material;
    bool hasTexture = false;
    bool isSkyboxObject = false;
};
