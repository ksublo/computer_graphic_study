#version 330 core

in vec3 FragPos; 
in vec3 Normal;  

uniform vec3 lightPosition;   
uniform vec3 lightColor;      
uniform float lightIntensity; 

uniform vec3 viewPos;         
uniform vec3 objectColor;    

out vec4 FragColor;

void main() {
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPosition - FragPos);
    
    vec3 ambient = 0.1 * lightColor;

    // Diffuse 
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor * lightIntensity;

    // Specular 
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), 5.0); 
    vec3 specular = 4.0 * spec * lightColor * lightIntensity; 

    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}
