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

const char* vertex_shader_camera =
"#version 330\n"
"layout(location=0) in vec3 vp;\n"
"layout(location=1) in vec3 normal;\n"
"out vec3 fragNormal;\n"
"uniform mat4 modelMatrix;\n"
"uniform mat4 viewMatrix;\n"
"uniform mat4 projectionMatrix;\n"
"void main () {\n"
"     gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);\n"
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

const char* fragment_shader_green =
"#version 330\n"
"in vec3 fragNormal;\n"
"out vec4 fragColor;\n"
"void main () {\n"
"    fragColor = vec4(80.0 / 255.0, 184.0 / 255.0, 79.0 / 255.0, 1.0);\n"
"}";

const char* vertex_shader_light =
"#version 330 core\n"
"layout(location = 0) in vec3 in_Position;\n"
"layout(location = 1) in vec3 in_Normal;\n"
"uniform mat4 modelMatrix;\n"
"uniform mat4 viewMatrix;\n"
"uniform mat4 projectionMatrix;\n"
"uniform mat3 normalMatrix;\n"
"out vec3 ex_worldPosition;\n"
"out vec3 ex_worldNormal;\n"
"void main() {\n"
"    ex_worldPosition = vec3(modelMatrix * vec4(in_Position, 1.0f));\n"
"    ex_worldNormal = normalize(normalMatrix * in_Normal);\n"
"    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0f);\n"
"}\n";

const char* fragment_shader_light =
"#version 330 core\n"
"in vec3 ex_worldPosition;\n"
"in vec3 ex_worldNormal;\n"
"out vec4 out_Color;\n"
"void main() {\n"
"    vec3 lightPosition = vec3(0.0, 0.0, 0.0);\n"
"    vec3 lightColor = vec3(1.0, 1.0, 1.0);\n"
"    vec3 objectColor = vec3(0.385, 0.647, 0.812);\n"
"    vec3 lightDirection = normalize(lightPosition - ex_worldPosition);\n"
"    float diff = max(dot(ex_worldNormal, lightDirection), 0.0);\n"
"    vec3 diffuse = diff * lightColor * objectColor;\n"
"    vec3 ambient = 0.1 * objectColor;\n"
"    vec3 finalColor = ambient + diffuse;\n"
"    out_Color = vec4(finalColor, 1.0f);\n"
"}\n";

