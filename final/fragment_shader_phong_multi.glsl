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
    float cutoff;          
    int type;              
};

uniform Light lights[MAX_LIGHTS];
uniform int numberOfLights;


uniform vec3 spotDir;  
uniform vec3 spotPos; 

in vec3 FragPos;
in vec3 Normal;

uniform vec3 viewPos;

out vec4 FragColor;

vec3 objectColor = vec3(0.5f, 0.5f, 0.5f);

float calculateAttenuation(float distance, float constant, float linear, float quadratic) {
    return 1.0 / (constant + linear * distance + quadratic * (distance * distance));
}

vec3 calculateAmbient(vec3 lightColor) {
    return 0.1 * lightColor;
}

vec3 calculateDiffuse(vec3 lightColor, vec3 lightDir, vec3 normal, float attenuation) {
    float diff = max(dot(normal, lightDir), 0.0);
    return diff * lightColor * attenuation;
}

vec3 calculateSpecular(vec3 lightColor, vec3 lightDir, vec3 viewDir, vec3 normal, float attenuation) {
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 20.0);
    return 5.0 * spec * lightColor * attenuation;
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
        lightDir = normalize(spotPos - fragPos); 
        float distance = length(spotPos - fragPos); 
        attenuation = calculateAttenuation(distance, light.constantFactor, light.linearFactor, light.quadraticFactor);

        float theta = dot(lightDir, normalize(-spotDir)); 
        float spotEffect = smoothstep(light.cutoff - 0.05, light.cutoff, theta);
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

    FragColor = vec4(result * objectColor, 1.0);
}