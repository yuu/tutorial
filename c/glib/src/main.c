#include <glib.h>
#include <stdio.h>
#include <unistd.h>

#include "mygui.h"

Display *xdisp;
Window xwin;
EGLDisplay display = NULL;
EGLContext context = NULL;
EGLSurface surface = NULL;

gboolean dispatch_cb(gpointer data) {
    printf(data);
    glClearColor(0.25f, 0.25f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    eglSwapBuffers(display, surface);

    sleep(4);

    return FALSE;
}

static gpointer thread_main(gpointer data) {
    printf("start thread func\n");
    GMainContext *ctx = data;
    GMainLoop *loop = g_main_loop_new(ctx, FALSE);

    // GLES/EGL
    if (initializeX11(&xdisp, &xwin)) {
        printf("error init x\n");
    }

    if (initializeEGL(xdisp, xwin, &display, &context, &surface) < 0) {
        printf("Error initializeEGL\n");
    }

    g_main_loop_run(loop);

    return NULL;
}

int main() {
    GMainContext *ctx = g_main_context_new();
    printf("before: make thread\n");
    GError *error;
    g_thread_try_new("renderer thread", thread_main, g_main_context_ref(ctx),
                     &error);
    printf("after: make thread\n");

    sleep(2);
    g_main_context_invoke_full(ctx, G_PRIORITY_DEFAULT, dispatch_cb,
                               "Hello My World\n", NULL);
    printf("invoke one\n");
    g_main_context_invoke_full(ctx, G_PRIORITY_DEFAULT, dispatch_cb,
                               "Second World\n", NULL);
    printf("invoke two\n");

    sleep(100);

    return 0;
}