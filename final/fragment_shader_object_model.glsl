#version 330 core

in vec3 fragNormal;     
in vec2 fragTexCoords;  
in vec3 fragTangent;   

uniform sampler2D textureUnit;        

out vec4 FragColor;

void main() {

    vec3 bitangent = cross(fragNormal, fragTangent);

    vec3 baseColor = texture(textureUnit, fragTexCoords).rgb;

    FragColor = vec4(baseColor, 1.0);
}
