#include <GL/glew.h>
#include <GLFW/glfw3.h>

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <stdio.h>
#include "shader.h"
#include "object.h"
#include "bushes.h"
#include "gift.h"

float a[] = {
     -.5f, -.5f, .5f,  0, 0, 1,
     -.5f, .5f, .5f,  0, 0, 1,
       .5f, .5f, .5f,  0, 0, 1,
       .5f, -.5f, .5f,  0, 0, 1
};

const char* vertex_shader =
"#version 330\n"
"layout(location=0) in vec3 vp;\n"
"layout(location=1) in vec3 normal;\n"
"out vec3 fragNormal;\n"  
"uniform mat4 modelMatrix;\n"
"void main () {\n"
"     gl_Position = modelMatrix * vec4(vp, 1.0);\n"
"     fragNormal = normal;\n"  
"}";

const char* fragment_shader =
"#version 330\n"
"in vec3 fragNormal;\n"  
"out vec4 frag_colour;\n"
"void main () {\n"
"     vec3 color = fragNormal * 0.5 + 0.5;\n"  
"     frag_colour = vec4(color, 1.0);\n"  
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
 
    Object obj1(bushes, sizeof(bushes));
    Object obj2(gift, sizeof(gift));


    glm::mat4 M = glm::mat4(1.0f);
    constexpr float angle = glm::radians(2.0f);
    float myView = 0.3f;
    M = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
    M = glm::rotate(M, angle, glm::vec3(1.0f, 0.0f, 0.0f));
    M = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, myView));
    M = glm::scale(glm::mat4(1.5f), glm::vec3(1.5f));

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /*shader.use();
        shader.setUniformMatrix4fv("modelMatrix", M);

        obj1.draw(0, 8730);*/

        shader.use();
        shader.setUniformMatrix4fv("modelMatrix", M);

        obj2.draw(0, 66624);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
