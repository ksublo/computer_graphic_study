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

    GLuint shaderProgram = create_shader_program();
    GLuint shaderProgram1 = create_shader_program1();
    GLuint shaderProgram2 = create_shader_program2();
    GLuint shaderProgram3 = create_shader_program3();
    GLuint shaderProgram4 = create_shader_program4();

    Object object(obj1, sizeof(obj1));
    Object object1(obj2, sizeof(obj2));
    Object object2(obj3, sizeof(obj3));

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);
        object.draw(0, 3);

        glUseProgram(shaderProgram1);
        object.draw(3, 6);

        glUseProgram(shaderProgram2);
        object1.draw(0, 6);

        glUseProgram(shaderProgram3);
        object1.draw(6, 12);

        glUseProgram(shaderProgram4);
        object1.draw(12, 18);

        glUseProgram(shaderProgram2);
        object2.draw(0, 6);

        glUseProgram(shaderProgram);
        object2.draw(6, 9);

        glUseProgram(shaderProgram1);
        object2.draw(9, 15);

        glUseProgram(shaderProgram3);
        object2.draw(15, 21);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
