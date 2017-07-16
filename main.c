/*
* @Author: otae
* @Date:   2017-07-15 11:33:09
* @Last Modified by:   otae
* @Last Modified time: 2017-07-16 10:04:35
*/

#include <X11/Xlib.h>
#include <X11/X.h>
#include <stdio.h>

#include <X11/Xutil.h>
#include <stdbool.h>
#include "Xdata.h"

void take_screenshot(t_graphic_context context);
void take_part_screenshot(t_graphic_context context, int x, int y, int xl, int yl);

static void draw_selection_square(t_graphic_context context) {

	XEvent event;
	bool record_square = false;
	int init_pos[2];
	int mouse_pos[2];

	for (;;)
	{
		XNextEvent(context.display, &event);

		switch( event.type ) {
			case MotionNotify:
				mouse_pos[0] = event.xmotion.x;
				mouse_pos[1] = event.xmotion.y;
			break;
			case ButtonPress:
				record_square = true;
				init_pos[0] = event.xmotion.x;
				init_pos[1] = event.xmotion.y;
			break;
			case ButtonRelease:
			if ((mouse_pos[0] >= init_pos[0] && mouse_pos[1] >= init_pos[1]))
				take_part_screenshot(context, init_pos[0], init_pos[1],
					mouse_pos[0], mouse_pos[1]);
				return ;
			break;
			case KeyPress:
			//	return ;
			break;
		}
		XClearWindow(context.display, context.window);
		if (record_square && (mouse_pos[0] >= init_pos[0] && mouse_pos[1] >= init_pos[1]))
		{
			XFillRectangle(context.display, context.window, context.gc, init_pos[0], init_pos[1],
				mouse_pos[0] - init_pos[0], mouse_pos[1] - init_pos[1]);
		}
	}
}

int main(int ac, char **av) {

	t_graphic_context context;

	Xinit(&context);
	if (ac == 1) {
		take_screenshot(context);
		return (0);
	}
	draw_selection_square(context);
	Xdelete(context);
}