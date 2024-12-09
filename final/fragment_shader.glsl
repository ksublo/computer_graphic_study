#version 330

in vec3 fragNormal;
in vec2 fragTexCoords;

out vec4 frag_colour;

void main() {
    vec3 baseColor;

    baseColor = fragNormal * 0.5 + 0.5;

    frag_colour = vec4(baseColor, 1.0);
}
