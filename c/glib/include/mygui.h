#pragma once

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <X11/Xlib.h>

#include <stdio.h>

int initializeEGL(Display *xdisp, Window xwindow, EGLDisplay *disp,
                  EGLContext *ctx, EGLSurface *surf) {
    EGLDisplay display;
    display = eglGetDisplay((EGLNativeDisplayType)xdisp);
    *disp = display;
    if (display == EGL_NO_DISPLAY) {
        printf("Error eglGetDisplay\n");
        return -1;
    }
    if (!eglInitialize(display, NULL, NULL)) {
        printf("Error eglInitialize\n");
        return -1;
    }

    EGLint attr[] = {
        EGL_RED_SIZE,
        1,
        EGL_GREEN_SIZE,
        1,
        EGL_BLUE_SIZE,
        1,
        EGL_SURFACE_TYPE,
        EGL_WINDOW_BIT,
        EGL_RENDERABLE_TYPE,
        EGL_OPENGL_ES2_BIT,
        EGL_NONE,
    };

    EGLConfig config = NULL;
    EGLint numConfigs = 0;
    if (!eglChooseConfig(display, attr, &config, 1, &numConfigs)) {
        printf("error eglChooseConfig\n");
        return -1;
    }
    if (numConfigs != 1) {
        printf("error numCOnfigs\n");
        return -1;
    }

    EGLSurface surface;
    surface = eglCreateWindowSurface(display, config, xwindow, NULL);
    if (surface == EGL_NO_SURFACE) {
        printf("error eglCreateWindowSurface\n");
        return -1;
    }
    *surf = surface;

    EGLint ctxattr[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE,
    };
    EGLContext context;
    context = eglCreateContext(display, config, EGL_NO_CONTEXT, ctxattr);
    if (context == EGL_NO_CONTEXT) {
        printf("error eglCreateContext\n");
        return -1;
    }
    *ctx = context;
    eglMakeCurrent(display, surface, surface, context);

    return 0;
}

int initializeX11(Display **display, Window *window) {
    Display *xdisplay = XOpenDisplay(NULL);
    if (xdisplay == NULL) {
        printf("Error XOpenDisplay\n");
        return -1;
    }

    Window xwindow = XCreateSimpleWindow(
        xdisplay, DefaultRootWindow(xdisplay), 100, 100, 640, 480, 1,
        BlackPixel(xdisplay, 0), WhitePixel(xdisplay, 0));

    XMapWindow(xdisplay, xwindow);

    *display = xdisplay;
    *window = xwindow;

    return 0;
}