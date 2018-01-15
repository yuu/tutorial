#pragma once

#include <EGL/eglplatform.h>
#include <stdlib.h>

EGLNativeDisplayType backend_display_open(const char *display_name);
EGLNativeWindowType backend_window_create(EGLNativeDisplayType disp, int32_t x,
                                          int32_t y, uint32_t w, uint32_t h);