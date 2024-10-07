#include <GL/glew.h>
#include <glm/glm.hpp>

class Shader {
public:
    Shader(const char* vertexSource, const char* fragmentSource);
    ~Shader();

    void use() const;
    void setUniformMatrix4fv(const char* name, const glm::mat4& matrix) const;

private:
    GLuint programID;  
    GLuint compileShader(const char* shaderSource, GLenum shaderType); 
};
