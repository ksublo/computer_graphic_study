#include <GL/glew.h>

class Shader {
public:
    Shader(const char* vertexSource, const char* fragmentSource);
    ~Shader();

    void use() const;  

private:
    GLuint programID;  
    GLuint compileShader(const char* shaderSource, GLenum shaderType); 
};
