#include <GL/glew.h>

class Shader {
public:
    Shader(const char* sourceCode, GLenum shaderType);  
    ~Shader();  
    void compile() const;  

private:
    GLuint id;  
    GLenum type;  
    const char* source;  

    friend class ShaderProgram;  
};
