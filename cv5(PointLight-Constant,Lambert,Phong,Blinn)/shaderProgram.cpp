#include "ShaderProgram.h"
#include <glm/gtc/type_ptr.hpp> 
#include <iostream>

ShaderProgram::ShaderProgram(const char* vertexFile, const char* fragmentFile) : camera(nullptr), light(nullptr) {

    Shader vertexShader(vertexFile, GL_VERTEX_SHADER);
    Shader fragmentShader(fragmentFile, GL_FRAGMENT_SHADER);

    programID = loadShader(vertexFile, fragmentFile);
    if (programID == 0) {
        cerr << "Shader program loading failed!" << endl;
        return;
    }
}

bool ShaderProgram::setShaderProgram() const {
    glValidateProgram(programID);
    GLint status;
    glGetProgramiv(programID, GL_VALIDATE_STATUS, &status);
    return status == GL_TRUE;
}

void ShaderProgram::use() const {
    glUseProgram(programID);
}

void ShaderProgram::setUniformMatrix4fv(const char* name, const glm::mat4& matrix) const {
    GLint location = glGetUniformLocation(programID, name);
    if (location == -1) {
        std::cerr << "Could not find uniform variable '" << name << "' in shader program." << std::endl;
    }
    else {
        glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
    }
}

void ShaderProgram::update() {
    if (camera) {
        use();
        setUniformMatrix4fv("viewMatrix", camera->getViewMatrix());
        setUniformMatrix4fv("projectionMatrix", camera->getProjectionMatrix());
    }

    if (light) {
        use();
        GLint lightPosLocation = glGetUniformLocation(programID, "lightPosition");
        GLint lightColorLocation = glGetUniformLocation(programID, "lightColor");
        GLint lightIntensityLocation = glGetUniformLocation(programID, "lightIntensity");

        if (lightPosLocation != -1) {
            glUniform3fv(lightPosLocation, 1, glm::value_ptr(light->getPosition()));
        }
        if (lightColorLocation != -1) {
            glUniform3fv(lightColorLocation, 1, glm::value_ptr(light->getColor()));
        }
        if (lightIntensityLocation != -1) {
            glUniform1f(lightIntensityLocation, light->getIntensity());
        }

        GLint objectColorLocation = glGetUniformLocation(programID, "objectColor");
        if (objectColorLocation != -1) {
            glm::vec3 objectColor(0.5f, 0.5f, 0.5f); 
            glUniform3fv(objectColorLocation, 1, glm::value_ptr(objectColor));
        }
        else {
            std::cerr << "Uniform 'objectColor' not found in shader program." << std::endl;
        }
    }
    
}


void ShaderProgram::setCamera(Camera* cam) {
    this->camera = cam;
    camera->registerObserver(this);
}

void ShaderProgram::setLight(Light* light) {
    this->light = light;
    light->registerObserver(this);
}
