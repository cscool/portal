#pragma once
#include "log.h"
#include <X11/Xlib.h>
#include <X11/X.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


extern int xres;
extern int yres;

extern Display *dpy;
extern Window win;
extern GLXContext glc;

#ifndef _XWIN_H
#define _XWIN_H

void initXWindows(void);
void cleanupXWindows(void);
void setup_screen_res(const int, const int);

void set_title(void);

#endif /* xwin.h */
