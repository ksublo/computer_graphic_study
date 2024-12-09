#version 330

in vec3 fragNormal;      
in vec2 fragTexCoords;  

uniform sampler2D textureUnit; 
uniform bool hasTexture;       

out vec4 frag_colour; 

void main() {
    vec3 baseColor;

    if (hasTexture) {
        baseColor = texture(textureUnit, fragTexCoords).rgb;
    }
    else {
        baseColor = fragNormal * 0.5 + 0.5;
    }

    frag_colour = vec4(baseColor, 1.0);
}
