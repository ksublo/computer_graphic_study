#include "shader.h"
#include <stdio.h>

const char* vertex_shader =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"void main () {"
"     gl_Position = vec4 (vp, 1.0);"
"}";

const char* fragment_shader =
"#version 330\n"
"out vec4 frag_colour;"
"void main () {"
"     frag_colour = vec4 (0.6, 0.0, 0.3, 1.0);"
"}";

const char* fragment_shader1 =
"#version 330\n"
"out vec4 frag_colour;"
"void main () {"
"     frag_colour = vec4 (0.8, 0.0, 0.3, 1.0);"
"}";

const char* fragment_shader2 =
"#version 330\n"
"out vec4 frag_colour;"
"void main () {"
"     frag_colour = vec4 (0.0, 0.4, 0.6, 1.0);"
"}";

const char* fragment_shader3 =
"#version 330\n"
"out vec4 frag_colour;"
"void main () {"
"     frag_colour = vec4 (0.0, 0.6, 0.6, 1.0);"
"}";

const char* fragment_shader4 =
"#version 330\n"
"out vec4 frag_colour;"
"void main () {"
"     frag_colour = vec4 (0.1, 0.5, 0.5, 1.0);"
"}";

GLuint compile_shader(const char* shader_src, GLenum shader_type) {
    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &shader_src, NULL);
    glCompileShader(shader);

    return shader;
}

GLuint create_shader_program() {
    GLuint vertexShader = compile_shader(vertex_shader, GL_VERTEX_SHADER);
    GLuint fragmentShader = compile_shader(fragment_shader, GL_FRAGMENT_SHADER);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

GLuint create_shader_program1() {
    GLuint vertexShader = compile_shader(vertex_shader, GL_VERTEX_SHADER);
    GLuint fragmentShader = compile_shader(fragment_shader1, GL_FRAGMENT_SHADER);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
   
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

GLuint create_shader_program2()
{
    GLuint vertexShader = compile_shader(vertex_shader, GL_VERTEX_SHADER);
    GLuint fragmentShader = compile_shader(fragment_shader2, GL_FRAGMENT_SHADER);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

GLuint create_shader_program3()
{
    GLuint vertexShader = compile_shader(vertex_shader, GL_VERTEX_SHADER);
    GLuint fragmentShader = compile_shader(fragment_shader3, GL_FRAGMENT_SHADER);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

GLuint create_shader_program4()
{
    GLuint vertexShader = compile_shader(vertex_shader, GL_VERTEX_SHADER);
    GLuint fragmentShader = compile_shader(fragment_shader4, GL_FRAGMENT_SHADER);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}
