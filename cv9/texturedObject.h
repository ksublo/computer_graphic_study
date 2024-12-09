#pragma once
#include "Object.h"
#include "Texture.h"

class TexturedObject : public Object {
public:
    TexturedObject(float* vertices, size_t size, int vertexCount, Texture* texture);

    void bind() const;
    void draw() const;

    int getTextureUnit() const;

private:
    Texture* texture; 
};
