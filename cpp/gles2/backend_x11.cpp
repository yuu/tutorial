#include "backend.h"

#include <X11/Xlib.h>

#include <stdio.h>

EGLNativeDisplayType backend_display_open(const char *display_name) {
    Display *xdisplay = XOpenDisplay(display_name);
    if (xdisplay == NULL)
        return NULL;

    return xdisplay;
}

EGLNativeWindowType backend_window_create(EGLNativeDisplayType disp, int32_t x,
                                          int32_t y, uint32_t w, uint32_t h) {
    Window xwindow =
        XCreateSimpleWindow(disp, DefaultRootWindow(disp), x, y, w, h, 1,
                            BlackPixel(disp, 0), WhitePixel(disp, 0));

    XMapWindow(disp, xwindow);

    return xwindow;
}