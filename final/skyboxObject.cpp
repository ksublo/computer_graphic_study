#include "SkyboxObject.h"
#include <GL/glew.h>
#include <SOIL.h>
#include <iostream>

SkyboxObject::SkyboxObject(float* vertices, size_t size, int vertexCount) 
    : Object(vertices, size, vertexCount) {
   
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0); 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindVertexArray(0);
}
