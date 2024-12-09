#pragma once
#include <GL/glew.h>
#include "Shader.h"
#include "shaderLoader.h"
#include "observer.h"  
#include "camera.h"  
#include "light.h"
#include <glm/glm.hpp>
#include "material.h"

class ShaderProgram : public Observer, ShaderLoader {
public:
    ShaderProgram(const char* vertexFile, const char* fragmentFile);

    bool setShaderProgram() const;

    void use() const;
    void setUniformMatrix4fv(const char* name, const glm::mat4& matrix) const;
    void setUniform(const char* name, bool value) const;

    void update() override;

    void setCamera(Camera* cam);
    void setLights(std::vector<Light>* lights);
    void setMaterial(const Material& material) const;

    void setTextureUnit(const char* name, int unit);

    void uploadLightToShader(const Light& light, size_t index);

private:
    GLuint programID; 
    Camera* camera;  
    std::vector<Light>* lights;
};
