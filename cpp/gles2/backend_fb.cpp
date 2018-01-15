#include "backend.h"

#include <EGL/eglvivante.h>

#include <unistd.h>

EGLNativeDisplayType backend_display_open(const char *display_name) {
    int num = 0;
    if (display_name != NULL)
        num = atoi(display_name);

    EGLNativeDisplayType native_display = fbGetDisplayByIndex(num);
    if (!native_display)
        return NULL;

    return native_display;
}

EGLNativeWindowType backend_window_create(EGLNativeDisplayType disp, int32_t x,
                                          int32_t y, uint32_t w, uint32_t h) {
    EGLNativeWindowType native_window = fbCreateWindow(disp, x, y, w, h);
    if (!native_window)
        return NULL;

    return native_window;
}