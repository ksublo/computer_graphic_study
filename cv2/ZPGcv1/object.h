#include <GL/glew.h>

class Object {
public:
    Object(float* vertices, size_t size);
    ~Object();
    void draw(GLint first, GLint count) const;

private:
    GLuint VAO, VBO;
};

