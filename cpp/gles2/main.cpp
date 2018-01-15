#include "backend.h"
#include "eglwrap.hpp"
#include "img.hpp"
#include "png.hpp"

#include <GLES2/gl2.h>

#include <unistd.h>
#include <iostream>

int main(int, char **) {
    auto png = loadPng("./sample.png");

    int w = png.width;
    int h = png.height;
    int s = w * png.has_alpha ? 4 : 3;

    EGLNativeDisplayType xdisplay = backend_display_open(nullptr);
    if (xdisplay == nullptr) {
        std::cerr << "Error XOpenDisplay." << std::endl;
        exit(EXIT_FAILURE);
    }

    EGLNativeWindowType xwindow = backend_window_create(xdisplay, 0, 0, w, h);

    EGLDisplay display = nullptr;
    EGLContext context = nullptr;
    EGLSurface surface = nullptr;

    if (initializeEGL(xdisplay, xwindow, &display, &context, &surface) < 0) {
        std::cerr << "Error initializeEGL." << std::endl;
        exit(EXIT_FAILURE);
    }

    // init shader
    GLuint shader_program;
    {
        GLuint shader_vtx = CreateGLShader(&shader_code_vtx, GL_VERTEX_SHADER);
        GLuint shader_frg =
            CreateGLShader(&shader_code_frg, GL_FRAGMENT_SHADER);
        shader_program = CreateGLProgram(shader_vtx, shader_frg);
    }
    // init prog
    {
        GLuint loc_vtxcoord_ =
            glGetAttribLocation(shader_program, "a_Position");
        GLuint loc_texcoord_ =
            glGetAttribLocation(shader_program, "a_TexCoord");
        glEnableVertexAttribArray(loc_vtxcoord_);
        glEnableVertexAttribArray(loc_texcoord_);

        glVertexAttribPointer(loc_vtxcoord_, 2, GL_FLOAT, GL_FALSE, 0,
                              vtx_coord);
        glVertexAttribPointer(loc_texcoord_, 2, GL_FLOAT, GL_FALSE, 0,
                              tex_coord);

        GLint loc_sampler = glGetUniformLocation(shader_program, "tex");
        glUseProgram(shader_program);
        glUniform1i(loc_sampler, 0);
        glUseProgram(0);
    }
    // init texture
    GLuint texture_id;
    { glGenTextures(1, &texture_id); }

    glBindTexture(GL_TEXTURE_2D, texture_id);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(GL_TEXTURE_2D, 0, png.has_alpha ? GL_RGBA : GL_RGB, w, h, 0,
                 png.has_alpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, png.data);

    GLint error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("[%s] glTexImage2D error: 0x%05x\n", __func__, error);
    }

    int count = 0;
    glViewport(0, 0, w, h);
    glUseProgram(shader_program);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    while (true) {
        count++;
        if (count >= 10000) {
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        eglSwapBuffers(display, surface);
        usleep(1000);
    }

    return 0;
}
