#version 330

#define MAX_LIGHTS 6

struct Light {
    vec3 position;
    vec3 direction;
    vec3 color;
    float intensity;
    float constantFactor;
    float linearFactor;
    float quadraticFactor;
    int type; 
};
uniform Light lights[MAX_LIGHTS];
uniform int numberOfLights;

struct Material {
    vec3 ambient;  
    vec3 diffuse; 
    vec3 specular; 
    float shininess; 
};
uniform Material material;

in vec3 FragPos;
in vec3 Normal;

uniform vec3 viewPos;

vec3 objectColor = vec3(0.5f, 0.5f, 0.5f);

out vec4 FragColor;

float calculateAttenuation(float distance, float constant, float linear, float quadratic) {
    return 1.0 / (constant + linear * distance + quadratic * (distance * distance));
}

vec3 calculateAmbient(vec3 lightColor) {
    return material.ambient * lightColor;
}

vec3 calculateDiffuse(vec3 lightColor, vec3 lightDir, vec3 normal, float attenuation) {
    float diff = max(dot(normal, lightDir), 0.0);
    return diff * lightColor * material.diffuse * attenuation;
}

vec3 calculateSpecular(vec3 lightColor, vec3 lightDir, vec3 viewDir, vec3 normal, float attenuation) {
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    return spec * lightColor * material.specular * attenuation;
}

vec3 calculateLightContribution(Light light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir;
    float attenuation = 1.0;

    if (light.type == 0) { 
        lightDir = normalize(light.position - fragPos);
        float distance = length(light.position - fragPos);
        attenuation = calculateAttenuation(distance, light.constantFactor, light.linearFactor, light.quadraticFactor);
    }
    else if (light.type == 1) { 
        lightDir = normalize(-light.direction);
        attenuation = 1.0; 
    }
    else if (light.type == 2) { 
        lightDir = normalize(light.position - fragPos);
        float distance = length(light.position - fragPos);
        attenuation = calculateAttenuation(distance, light.constantFactor, light.linearFactor, light.quadraticFactor);

        float theta = dot(lightDir, normalize(-light.direction));
        float spotEffect = smoothstep(0.9 * light.intensity, light.intensity, theta);
        attenuation *= spotEffect;
    }

    vec3 ambient = calculateAmbient(light.color);
    vec3 diffuse = calculateDiffuse(light.color, lightDir, normal, attenuation);
    vec3 specular = calculateSpecular(light.color, lightDir, viewDir, normal, attenuation);

    return ambient + diffuse + specular;
}

void main() {
    vec3 normal = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 result = vec3(0.0);

    for (int i = 0; i < numberOfLights; i++) {
        result += calculateLightContribution(lights[i], normal, FragPos, viewDir);
    }

    result *= objectColor;
    FragColor = vec4(result, 1.0);
}
