#pragma once
#include "Object.h"
#include "Texture.h" 

#include <vector>
#include <string>

class SkyboxObject : public Object {
public:
    SkyboxObject(float* vertices, size_t size, int vertexCount, Texture* texture);
    ~SkyboxObject();

    void bind() const; 
    void draw() const; 

private:
    Texture* texture;
};