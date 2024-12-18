#include "Object.h"
#include "Transformation.h"
#include "ShaderProgram.h"

class DrawableObject {
public:
    DrawableObject(Object* object, ShaderProgram* shaderProgram);
    void setTransformation(const Transformation& transform); 
    void modifyTransformation(const Transformation& transform);
    void draw();  
    

private:
    Object* object;  
    Transformation transformation;  
    ShaderProgram* shaderProgram;
};

