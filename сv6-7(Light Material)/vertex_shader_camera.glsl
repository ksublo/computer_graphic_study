#version 330

layout(location = 0) in vec3 position;  
layout(location = 1) in vec3 normal;   

uniform mat4 modelMatrix;            
uniform mat4 viewMatrix;              
uniform mat4 projectionMatrix;                    

out vec3 fragNormal;                   

void main() {
    fragNormal = normalize(mat3(transpose(inverse(modelMatrix))) * normal);
    
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
}
