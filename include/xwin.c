#include "xwin.h"

void cleanupXWindows(void)
{
	 Log("calling XDestroyWindow\n");
	 XDestroyWindow(dpy, win);
	 Log("calling XCloseDisplay\n");
	 XCloseDisplay(dpy);
	 Log("done with cleanupXWindows\n");
}

void setup_screen_res(const int w, const int h)
{
	 xres = w;
	 yres = h;
}

void set_title(void)
{
	 //Set the window title bar.
	 XMapWindow(dpy, win);
	 XStoreName(dpy, win, "CS335 - OpenGL Animation Template Under XWindows");
}

void initXWindows(void)
{
	 //Initialize XWindows for OpenGL
	 Window root;
	 GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
	 XVisualInfo *vi;
	 Colormap cmap;
	 XSetWindowAttributes swa;

	 setup_screen_res(640, 480);
	 dpy = XOpenDisplay(NULL);
	 if(dpy == NULL) {
		  printf("\ncannot connect to X server\n\n");
		  exit(EXIT_FAILURE);
	 }
	 root = DefaultRootWindow(dpy);
	 vi = glXChooseVisual(dpy, 0, att);
	 if(vi == NULL) {
		  printf("\nno appropriate visual found\n\n");
		  exit(EXIT_FAILURE);
	 } 
	 //else {
	 //	// %p creates hexadecimal output like in glxinfo
	 //	printf("\n\tvisual %p selected\n", (void *)vi->visualid);
	 //}
	 cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
	 swa.colormap = cmap;
	 swa.event_mask =
		  ExposureMask |
		  KeyPressMask |
		  KeyReleaseMask |
		  StructureNotifyMask |
		  SubstructureNotifyMask;
	 win = XCreateWindow(dpy, root, 0, 0, xres, yres, 0,
				vi->depth, InputOutput, vi->visual,
				CWColormap | CWEventMask, &swa);
	 set_title();
	 glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
	 glXMakeCurrent(dpy, win, glc);
}

