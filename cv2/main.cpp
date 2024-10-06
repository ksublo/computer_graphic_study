#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "shader.h"
#include "object.h"

float obj1[] = {
    0.2f, 0.2f, 0.0f,
    0.4f, 0.5f, 0.0f,
    0.6f, 0.2f, 0.0f,

    0.4f, 0.5f, 0.0f,
    0.6f, 0.2f, 0.0f,
    0.6f, 0.6f, 0.0f,

    0.6f, 0.2f, 0.0f,
    0.6f, 0.6f, 0.0f,
    0.8f, 0.3f, 0.0f,
};

float obj2[] = {
    -0.9f, 0.8f, 0.0f,
    -0.9f, 0.5f, 0.0f,
    -0.6f, 0.8f, 0.0f,

    -0.9f, 0.5f, 0.0f,
    -0.6f, 0.8f, 0.0f,
    -0.6f, 0.5f, 0.0f,

    -0.6f, 0.8f, 0.0f,
    -0.6f, 0.5f, 0.0f,
    -0.5f, 0.9f, 0.0f,

    -0.5f, 0.6f, 0.0f,
    -0.6f, 0.5f, 0.0f,
    -0.5f, 0.9f, 0.0f,

    -0.9f, 0.8f, 0.0f,
    -0.6f, 0.8f, 0.0f,
    -0.8f, 0.9f, 0.0f,

    -0.6f, 0.8f, 0.0f,
    -0.8f, 0.9f, 0.0f,
    -0.5f, 0.9f, 0.0f,
};

float obj3[] = {
    -0.7f, -0.4f, 0.0f,
    -0.3f, -0.4f, 0.0f,
    -0.3f, -0.7f, 0.0f,

    -0.7f, -0.4f, 0.0f,
    -0.3f, -0.7f, 0.0f,
    -0.7f, -0.7f, 0.0f,

    -0.7f, -0.4f, 0.0f,
    -0.3f, -0.4f, 0.0f,
    -0.5f, -0.2f, 0.0f,

    -0.3f, -0.4f, 0.0f,
    -0.5f, -0.2f, 0.0f,
    -0.4f, -0.1f, 0.0f,

    -0.3f, -0.4f, 0.0f,
    -0.2f, -0.3f, 0.0f,
    -0.4f, -0.1f, 0.0f,

    -0.3f, -0.4f, 0.0f,
    -0.2f, -0.3f, 0.0f,
    -0.3f, -0.7f, 0.0f,

    -0.2f, -0.6f, 0.0f,
    -0.2f, -0.3f, 0.0f,
    -0.3f, -0.7f, 0.0f,
};

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

static void error_callback(int error, const char* description) {
    printf("Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

static void window_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main(void) {

    if (!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);
    glewExperimental = GL_TRUE;
    glewInit();

    Shader shader(vertex_shader, fragment_shader);
    Shader shader1(vertex_shader, fragment_shader1);
    Shader shader2(vertex_shader, fragment_shader2);
    Shader shader3(vertex_shader, fragment_shader3);
    Shader shader4(vertex_shader, fragment_shader4);

    Object object(obj1, sizeof(obj1));
    Object object1(obj2, sizeof(obj2));
    Object object2(obj3, sizeof(obj3));

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        object.draw(0, 3);

        shader1.use();
        object.draw(3, 6);

        shader2.use();
        object1.draw(0, 6);

        shader3.use();
        object1.draw(6, 6);

        shader4.use();
        object1.draw(12, 6);

        shader2.use();
        object2.draw(0, 6);

        shader.use();
        object2.draw(6, 3);

        shader1.use();
        object2.draw(9, 6);

        shader3.use();
        object2.draw(15, 6);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
