#pragma once
#include <GL/glew.h>

class Object {
public:
    Object();
    Object(float* vertices, size_t size, int vertexCount);
    virtual ~Object();

    void bind() const;
    void draw() const;

protected:
    GLuint VAO, VBO;
    int vertexCount;
};
