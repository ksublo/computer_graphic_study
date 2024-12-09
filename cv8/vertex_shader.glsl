#version 330
layout(location=0) in vec3 vp;
layout(location=1) in vec3 normal;
out vec3 fragNormal;
uniform mat4 modelMatrix;

void main() {
    gl_Position = modelMatrix * vec4(vp, 1.0);
    fragNormal = normal;
}