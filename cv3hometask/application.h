#include "Scene.h"
#include "Shader.h"
#include <GLFW/glfw3.h>

class Application {
public:
    void run(); 
    void initScene();
    void initScene1();
    void switchScene(GLFWwindow* window, int key, int scancode, int action, int mods);
    void render();

private:

    Scene scene; 
    Scene scene1;
    bool sceneActive = true;
    bool rotationActive = false;

    void applyYRotationToScene(float rotationY);
    void applyTranslationToScene(Scene& scene, float x, float y);

};

