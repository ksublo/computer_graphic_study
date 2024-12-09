#pragma once
#include <GL/glew.h>

class Object {
public:
    Object(float* vertices, size_t size, int vertexCount);
    ~Object();

    void bind() const;
    void draw() const;

private:
    GLuint VAO, VBO;
    int vertexCount;
};
