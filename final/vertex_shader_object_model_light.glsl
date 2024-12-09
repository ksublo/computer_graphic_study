#version 330 

layout(location = 0) in vec3 position;  
layout(location = 1) in vec3 normal;     
layout(location = 2) in vec2 texCoords; 
layout(location = 3) in vec3 tangent;   

uniform mat4 modelMatrix;         
uniform mat4 viewMatrix;         
uniform mat4 projectionMatrix;   

out vec3 FragPos;        
out vec3 Normal;       
out vec2 TexCoords;      
out vec3 Tangent;        

void main() {
    FragPos = vec3(modelMatrix * vec4(position, 1.0));
    Normal = normalize(mat3(transpose(inverse(modelMatrix))) * normal);
    Tangent = normalize(mat3(transpose(inverse(modelMatrix))) * tangent);
    TexCoords = texCoords;
    gl_Position = projectionMatrix * viewMatrix * vec4(FragPos, 1.0);
}
