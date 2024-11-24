#include "ShaderProgram.h"
#include <glm/gtc/type_ptr.hpp> 
#include <iostream>

ShaderProgram::ShaderProgram(const char* vertexFile, const char* fragmentFile) : camera(nullptr), lights(nullptr){

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
    use();

    if (camera) {
        setUniformMatrix4fv("viewMatrix", camera->getViewMatrix());
        setUniformMatrix4fv("projectionMatrix", camera->getProjectionMatrix());

        GLint viewPosLocation = glGetUniformLocation(programID, "viewPos");
        if (viewPosLocation != -1) {
            glUniform3fv(viewPosLocation, 1, glm::value_ptr(camera->getPosition()));
        }

        GLint spotDirLoc = glGetUniformLocation(programID, "spotDir");
        if (spotDirLoc != -1) {
            glUniform3fv(spotDirLoc, 1, glm::value_ptr(camera->getForward()));
        }

        GLint spotPosLoc = glGetUniformLocation(programID, "spotPos");
        if (spotPosLoc != -1) {
            glUniform3fv(spotPosLoc, 1, glm::value_ptr(camera->getPosition()));
        }
    }


    if (lights) {
        GLint numLightsLoc = glGetUniformLocation(programID, "numberOfLights");
        if (numLightsLoc != -1) {
            glUniform1i(numLightsLoc, lights->size());
        }

        for (size_t i = 0; i < lights->size(); ++i) {
            const Light& light = (*lights)[i];
            uploadLightToShader(light, i);
        }
    }
}

void ShaderProgram::uploadLightToShader(const Light& light, size_t index) {
    std::string prefix = "lights[" + std::to_string(index) + "].";

    GLint typeLoc = glGetUniformLocation(programID, (prefix + "type").c_str());
    GLint posLoc = glGetUniformLocation(programID, (prefix + "position").c_str());
    GLint dirLoc = glGetUniformLocation(programID, (prefix + "direction").c_str());
    GLint colorLoc = glGetUniformLocation(programID, (prefix + "color").c_str());
    GLint intensityLoc = glGetUniformLocation(programID, (prefix + "intensity").c_str());
    GLint cutoffLoc = glGetUniformLocation(programID, (prefix + "cutoff").c_str());
    GLint constantLoc = glGetUniformLocation(programID, (prefix + "constantFactor").c_str());
    GLint linearLoc = glGetUniformLocation(programID, (prefix + "linearFactor").c_str());
    GLint quadraticLoc = glGetUniformLocation(programID, (prefix + "quadraticFactor").c_str());

    if (typeLoc != -1) glUniform1i(typeLoc, static_cast<int>(light.getType()));
    if (posLoc != -1) glUniform3fv(posLoc, 1, glm::value_ptr(light.getPosition()));
    if (dirLoc != -1) glUniform3fv(dirLoc, 1, glm::value_ptr(light.getDirection()));
    if (colorLoc != -1) glUniform3fv(colorLoc, 1, glm::value_ptr(light.getColor()));
    if (intensityLoc != -1) glUniform1f(intensityLoc, light.getIntensity());
    if (cutoffLoc != -1 && light.getType() == LightType::SPOT)
        glUniform1f(cutoffLoc, glm::cos(glm::radians(light.getCutoff())));

    float constant, linear, quadratic;
    light.getAttenuationFactors(constant, linear, quadratic);

    if (constantLoc != -1) glUniform1f(constantLoc, constant);
    if (linearLoc != -1) glUniform1f(linearLoc, linear);
    if (quadraticLoc != -1) glUniform1f(quadraticLoc, quadratic);
}


void ShaderProgram::setCamera(Camera* cam) {
    this->camera = cam;
    camera->registerObserver(this);
}


void ShaderProgram::setLights(std::vector<Light>* lights) {
    this->lights = lights; 

    if (lights) {
        for (Light& light : *lights) { 
            light.registerObserver(this);
        }
    }
}

void ShaderProgram::setMaterial(const Material& material) const {
    GLint ambientLoc = glGetUniformLocation(programID, "material.ambient");
    GLint diffuseLoc = glGetUniformLocation(programID, "material.diffuse");
    GLint specularLoc = glGetUniformLocation(programID, "material.specular");
    GLint shininessLoc = glGetUniformLocation(programID, "material.shininess");

    if (ambientLoc != -1) glUniform3fv(ambientLoc, 1, glm::value_ptr(material.getAmbient()));
    if (diffuseLoc != -1) glUniform3fv(diffuseLoc, 1, glm::value_ptr(material.getDiffuse()));
    if (specularLoc != -1) glUniform3fv(specularLoc, 1, glm::value_ptr(material.getSpecular()));
    if (shininessLoc != -1) glUniform1f(shininessLoc, material.getShininess());
}




