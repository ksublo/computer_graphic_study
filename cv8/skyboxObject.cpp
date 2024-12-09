#include "SkyboxObject.h"
#include <GL/glew.h>
#include <SOIL.h>
#include <iostream>

SkyboxObject::SkyboxObject(float* vertices, size_t size, int vertexCount, Texture* texture) 
    : Object(vertices, size, vertexCount), texture(texture) {
   
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0); 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindVertexArray(0);
}

SkyboxObject::~SkyboxObject() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void SkyboxObject::bind() const {
    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    texture->use();
}

void SkyboxObject::draw() const {
    bind();
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);
}


