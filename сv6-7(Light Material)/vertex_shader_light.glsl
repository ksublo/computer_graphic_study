#version 330 

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 FragPos; 
out vec3 Normal;  

void main() {
    FragPos = vec3(modelMatrix * vec4(position, 1.0));
    
    Normal = mat3(transpose(inverse(modelMatrix))) * normal;

    gl_Position = projectionMatrix * viewMatrix * vec4(FragPos, 1.0);
}
