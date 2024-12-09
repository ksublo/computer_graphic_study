#include "DrawableObject.h"

int DrawableObject::nextID = 1;

DrawableObject::DrawableObject(ObjectBase* object, ShaderProgram* shaderProgram, Material* material)
    : object(object), shaderProgram(shaderProgram), material(material), transformation(nullptr), texture(nullptr), id(nextID++){
}

void DrawableObject::setTransformation(Transformation* transform) {
    this->transformation = transform;
}

void DrawableObject::setTexture(Texture* texture) {
    this->texture = texture;
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
    shaderProgram->update();

    if (material) {
        shaderProgram->setMaterial(*material); 
    }

    if (transformation) {
        glm::mat4 matrix = transformation->getMatrix();
        shaderProgram->setUniformMatrix4fv("modelMatrix", matrix);
    }

    if (texture) {
        texture->use();
        int textureUnit = texture->getUnit();
        shaderProgram->setTextureUnit("textureUnit", textureUnit);
    }

    object->bind();
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

int DrawableObject::getID() const {
    return id; 
}

