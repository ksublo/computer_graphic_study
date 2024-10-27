#version 330 core

uniform vec3 lightColor;      
uniform float lightIntensity; 
uniform vec3 objectColor; 

out vec4 FragColor;

void main() {
    vec3 constantLight = lightColor * lightIntensity;
    vec3 result = constantLight * objectColor;
    FragColor = vec4(result, 1.0);
}

