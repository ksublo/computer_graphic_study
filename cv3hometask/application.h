#include "SceneInitializer.h"
#include <GLFW/glfw3.h>

class Application {
public:
    void run(); 
    void switchScene(GLFWwindow* window, int key, int scancode, int action, int mods);
    void render();

private:
    SceneInitializer sceneInitializer;
    Scene scene; 
    Scene scene1; 
    bool sceneActive = true;
    bool rotationActive = false;

    void applyYRotationToScene(float rotationY);
    void applyTranslationToScene(Scene& scene, float x, float y);

};

