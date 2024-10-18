#include <glm/glm.hpp>
#include "ShaderProgram.h"

class Transformation {
public:
    Transformation(); 

    void translate(float x, float y, float z);
    void rotate(float angle, float x, float y, float z);
    void scale(float a);

    void combine(const Transformation& other);

    void applyTransformation(ShaderProgram& shaderProgram, const char* uniformName) const;

private:
    glm::mat4 matrix; 
};

