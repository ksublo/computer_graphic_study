#pragma once
#include <GL/glew.h>
#include "Shader.h"
#include "shaderLoader.h"
#include "observer.h"  
#include "camera.h"  
#include "light.h"
#include <glm/glm.hpp>

class ShaderProgram : public Observer, ShaderLoader {
public:
    ShaderProgram(const char* vertexFile, const char* fragmentFile);

    bool setShaderProgram() const;
    void use() const;
    void setUniformMatrix4fv(const char* name, const glm::mat4& matrix) const;
    void update() override;
    void setCamera(Camera* cam);
    void setLight(Light* light);

private:
    GLuint programID; 
    Camera* camera;  
    Light* light;
};