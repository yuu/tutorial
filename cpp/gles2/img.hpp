#pragma once

#include <GLES2/gl2.h>

#include <stdlib.h> // calloc
#include <stdio.h>

/* shader prepare */
const char *shader_code_vtx =
#ifdef USE_X11_BACKEND
    "precision mediump float;\n"
#endif
    "attribute mediump vec4 a_Position;\n"
    "attribute mediump vec2 a_TexCoord;\n"
    "varying mediump vec2 v_TexCoord;\n"
    "\n"
    "void main(void) {\n"
    "  gl_Position = a_Position;\n"
    "  v_TexCoord  = a_TexCoord;\n"
    "}\n";

const char *shader_code_frg =
#ifdef USE_X11_BACKEND
    "precision mediump float;\n"
#endif
    "varying mediump vec2 v_TexCoord;\n"
    "uniform mediump sampler2D tex;\n"
    "void main()\n"
    "{\n"
    "    mediump vec2 uv = v_TexCoord.xy;\n"
    "    gl_FragColor = texture2D(tex, uv);\n"
    "}";

const GLfloat vtx_coord[] = {
    1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, -1.0f, 1.0f,
};

const GLfloat tex_coord[] = {
    1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
};

GLuint CreateGLShader(const char** shaderCode, GLenum shaderType) {
    GLuint shader = 0;
    GLint stat = 0;

    shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, shaderCode, 0);
    glCompileShader(shader);
    // Check the compile error
    glGetShaderiv(shader, GL_COMPILE_STATUS, (GLint*)&stat);
    if (GL_FALSE == stat) {
        GLint logLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, (GLint*)&logLen);

        void *tmp = calloc(logLen, sizeof(char));
        char *log = static_cast<char*>(tmp);
        int ans = 0;
        glGetShaderInfoLog(shader, logLen, NULL, log);
        printf("SHADER INFO: %s\n", log);

        glGetShaderiv(shader, GL_COMPILE_STATUS, &ans);
        printf("SHADER BUILD INFO: %d\n", ans);

        free(log);

        exit(1);
    }

    return shader;
}

GLuint CreateGLProgram(GLuint shaderVtx, GLuint shaderFrg) {
    GLuint program = 0;
    GLint stat = 0;

    program = glCreateProgram();
    glAttachShader(program, shaderFrg);
    glAttachShader(program, shaderVtx);

    // Link program to two shaders
    glLinkProgram(program);
    // Check the link error
    glGetProgramiv(program, GL_LINK_STATUS, (GLint*)&stat);
    if (GL_FALSE == stat) {
        GLint logLen = 0;
        glGetShaderiv(program, GL_INFO_LOG_LENGTH, (GLint*)&logLen);

        void *tmp = calloc(logLen, sizeof(char));
        char *log = static_cast<char*>(tmp);
        int ans = 0;
        glGetShaderInfoLog(program, logLen, NULL, log);
        printf("SHADER INFO: %s\n", log);

        glGetShaderiv(program, GL_COMPILE_STATUS, &ans);
        printf("SHADER BUILD INFO: %d\n", ans);

        free(log);

        exit(1);
    }

    glReleaseShaderCompiler();

    return program;
}
