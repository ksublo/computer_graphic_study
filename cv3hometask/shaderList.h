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