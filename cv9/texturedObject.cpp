#include "TexturedObject.h"

TexturedObject::TexturedObject(float* vertices, size_t size, int vertexCount, Texture* texture) 
    : Object(vertices, size, vertexCount), texture(texture) {

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(6 * sizeof(float)));


    glBindVertexArray(0);
}

void TexturedObject::bind() const {
    Object::bind();
    if (texture) {
        texture->use();
    }
}

void TexturedObject::draw() const {
    bind();
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);
}

int TexturedObject::getTextureUnit() const {
    return texture->getUnit();  
}
