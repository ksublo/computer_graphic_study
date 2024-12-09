#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;
layout(location = 3) in vec3 tangent; 

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 fragNormal;
out vec2 fragTexCoords;
out vec3 fragTangent; 

void main() {
    fragNormal = normalize(mat3(transpose(inverse(modelMatrix))) * normal);
    fragTexCoords = texCoords;
    fragTangent = normalize(mat3(transpose(inverse(modelMatrix))) * tangent); 

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
}

