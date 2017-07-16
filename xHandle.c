/*
* @Author: otae
* @Date:   2017-07-15 19:14:25
* @Last Modified by:   otae
* @Last Modified time: 2017-07-16 08:22:53
*/

#include <stdlib.h>
#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/X.h>
#include <stdio.h>

#include <X11/Xutil.h>

#include "Xdata.h"

static void fullscreen(Display* dpy, Window win) {
  Atom atoms[2] = { XInternAtom(dpy, "_NET_WM_STATE_FULLSCREEN", False), None };
  XChangeProperty(
		dpy, 
		win, 
		XInternAtom(dpy, "_NET_WM_STATE", False),
		4, 32, PropModeReplace, (const unsigned char*)atoms, 1);
}

void Xinit(t_graphic_context *out) {

	Display *display = XOpenDisplay(NULL);
	if (display == NULL) {
		printf("Error in Xinit: Unable to open Display\n");
		exit(-1);
	}
	Window root = DefaultRootWindow(display);
	XWindowAttributes gwa;

	XGetWindowAttributes(display, root, &gwa);

	int defaultScreen = DefaultScreen(display);
	int width = gwa.width;
	int height = gwa.height;
	out->width = width;
	out->height = height;

	XVisualInfo vinfo;
	XMatchVisualInfo(display, DefaultScreen(display), 32, TrueColor, &vinfo);
	XSetWindowAttributes attr;
	attr.colormap = XCreateColormap(display, DefaultRootWindow(display), vinfo.visual, AllocNone);
	attr.border_pixel = 0x00000000;
	attr.background_pixel = 0x50500010;

	Window window = XCreateWindow(display, root, 0, 0, width, height, 0,
		vinfo.depth, InputOutput, vinfo.visual, CWColormap | CWBorderPixel | CWBackPixel, &attr);
	fullscreen(display, window);
	XSelectInput(display, window, ExposureMask | KeyPressMask | PointerMotionMask | Button1MotionMask | ButtonPressMask | ButtonReleaseMask);
	XMapWindow(display, window);
	GC gc = XCreateGC(display, window, 0, 0);
	out->display = display;
	out->window = window;
	out->gc = gc;
	out->root = root;
}

void Xdelete(t_graphic_context context) {
	XCloseDisplay(context.display);
}
