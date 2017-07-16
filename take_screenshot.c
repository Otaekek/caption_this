/*
* @Author: otae
* @Date:   2017-07-15 21:47:59
* @Last Modified by:   otae
* @Last Modified time: 2017-07-16 09:50:28
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <X11/Xlib.h>
#include <X11/X.h>
#include <X11/Xutil.h>

#include <stdbool.h>
#include "Xdata.h"
#include <sys/types.h>
#include <pwd.h>

void drawbmp (char * filename, int WIDTH, int HEIGHT,
	unsigned char **redcount, unsigned char **greencount, unsigned char **bluecount);

static void get_desktop_path(char out[256]) {

	FILE *fp;
	char path[1035];

	fp = popen("echo $(xdg-user-dir DESKTOP)", "r");
	if (fp == NULL) {
		printf("Failed to run command\n" );
		exit(-1);
	}
	while (fgets(path, sizeof(path)-1, fp) != NULL) {
		strcpy(out, path);
	}
	if (strlen(out) < 1)
		exit(-1);
	out[strlen(out) - 1] = 0;
	pclose(fp);
}

static char *create_path_name() {
	
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[800];

	time (&rawtime);
	timeinfo = localtime(&rawtime);
	get_desktop_path(buffer);
	strcat(buffer, "/ScreenShot - ");
	strftime(buffer + strlen(buffer),sizeof(buffer) - strlen(buffer),"%d-%m-%Y %I:%M:%S",timeinfo);
	strcat(buffer, ".bmp");
	return (strdup(buffer));

}
void take_part_screenshot(t_graphic_context context, int x, int y, int xl, int yl) {	

	char *pathname = create_path_name();

	char **redcount = (char**)malloc((xl - x) * (sizeof(char*)));
	char **greencount = (char**)malloc((xl - x) * (sizeof(char*)));
	char **bluecount = (char**)malloc((xl - x) * (sizeof(char*)));

	for (int i = 0; i < (xl - x); i++) {
		redcount[i] = (char*)malloc(yl - y);
		greencount[i] = (char*)malloc(yl - y);
		bluecount[i] = (char*)malloc(yl - y);
	}
	XImage *image = XGetImage(context.display, context.root, 0,0,
		context.width, context.height, AllPlanes, ZPixmap);
	for (int i = 0; i < (xl - x); i++) {
		for (int j = 0; j < (yl - y); j++) {
			int pixel = XGetPixel(image,i + x,j + y);
			redcount[i][j] = (pixel & image->red_mask) >> 16;
			greencount[i][j] = (pixel & image->green_mask) >> 8;
			bluecount[i][j] = pixel & image->blue_mask;
		}
	}
	drawbmp(pathname, (xl - x), (yl - y),
		(unsigned char**)redcount, (unsigned char**)greencount, (unsigned char**)bluecount);
	for (int i = 0; i < (xl - x); i++) {
		free(redcount[i]);
		free(greencount[i]);
		free(bluecount[i]);
	}
	free(redcount);
	free(greencount);
	free(bluecount);
	free(pathname);
}

void take_screenshot(t_graphic_context context)
{
	take_part_screenshot(context, 0, 0, context.width, context.height);
}
