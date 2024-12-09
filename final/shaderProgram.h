/**
 *
 * @file shaderProgram.h
 * @brief Manages OpenGL shader programs, handling uniforms, camera updates, and light configuration
 *
 * @author Kseniia Blokhina
 * @login BLO0021
 *
 */
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

    void use() const;
    void setUniformMatrix4fv(const char* name, const glm::mat4& matrix) const;

    void update() override;

    void setCamera(Camera* cam);
    void setLights(std::vector<Light>* lights);
    void setMaterial(const Material& material) const;
    void setTextureUnit(const char* name, int unit);

private:

    GLuint programID; 
    Camera* camera;  
    std::vector<Light>* lights;

    void uploadLightToShader(const Light& light, size_t index);

};
