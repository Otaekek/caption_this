/*
* @Author: otae
* @Date:   2017-07-15 19:16:40
* @Last Modified by:   otae
* @Last Modified time: 2017-07-16 08:22:25
*/

#ifndef XDATA_H
# define XDATA_H

#include <X11/Xlib.h>
#include <X11/X.h>


typedef struct s_graphic_context {
	GC			gc;
	Display		*display;
	int			width;
	int			height;
	Window		window;
	Window		root;
}				t_graphic_context;

void Xinit(t_graphic_context *out);
void Xdelete(t_graphic_context context);

#endif