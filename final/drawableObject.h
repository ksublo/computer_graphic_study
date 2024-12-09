/**
 *
 * @file drawableObject.h
 * @brief Represents an object that can be drawn, with transformations, textures, and materials applied
 *
 * @author Kseniia Blokhina
 * @login BLO0021
 *
 */
#pragma once
#include "Transformation.h"
#include "TransformationGroup.h"
#include "ShaderProgram.h"
#include "Material.h"
#include "ObjectBase.h"
#include "Texture.h"

class DrawableObject {
public:

    DrawableObject(ObjectBase* object, ShaderProgram* shaderProgram, Material* material);

    void setTransformation(Transformation* transform);
    void setTexture(Texture* texture);
    void modifyTransformation(Transformation* transform);

    void draw();

    void setSkybox(bool isSkyboxObject);
    bool isSkybox();

    int getID() const;

private:

    ObjectBase* object;
    Transformation* transformation;  
    Texture* texture;
    ShaderProgram* shaderProgram;
    Material* material;
    bool isSkyboxObject = false;

    static int nextID;
    int id;
};
