#version 330

#define MAX_LIGHTS 6

struct Light {
    vec3 color;
    float intensity;
};

uniform Light lights[MAX_LIGHTS];
uniform int numberOfLights;

struct Material {
    vec3 ambient;  
};

uniform Material material;        

in vec2 TexCoords;

vec3 objectColor = vec3(0.5f, 0.5f, 0.5f);

out vec4 FragColor;

void main() {
    vec3 result = vec3(0.0);

    for (int i = 0; i < numberOfLights; i++) {
        vec3 ambient = material.ambient * lights[i].color * lights[i].intensity; 
        result += ambient;
    }

    result *= objectColor;  
    FragColor = vec4(result, 1.0);
}
