#pragma once
#include <GL/glew.h>
#include "Shader.h"
#include "observer.h"  // Include Observer interface
#include "camera.h"    // Include Camera to access its view matrix
#include <glm/glm.hpp>

class ShaderProgram : public Observer {
public:
    // Constructor
    ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader);

    // Set up the shader program
    bool setShaderProgram() const;

    // Activate the shader program
    void use() const;

    // Set a uniform matrix in the shader
    void setUniformMatrix4fv(const char* name, const glm::mat4& matrix) const;

    // Observer implementation
    void update() override;

    // Set the camera and register as an observer
    void setCamera(Camera* cam);

private:
    GLuint programID;  // Shader program ID
    Camera* camera;    // The camera we're observing
};
