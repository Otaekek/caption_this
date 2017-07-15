/*
* @Author: otae
* @Date:   217-07-15 12:00:53
* @Last Modified by:   otae
* @Last Modified time: 2017-07-15 12:11:21
*/

#include <strings.h>
#include <stdbool.h>

#define SCREEN_SHOT 0
#define PART_SCREEN_SHOT 1
#define ELSE 2

void poll_event(bool out[3]) {

}

void handle_event(const bool event[3]) {
	if (event[SCREEN_SHOT])
		screen_shot();
	else if (event[PART_SCREEN_SHOT])
		part_screen_shot();
	else if (event[ELSE])
		;
}

void deamon_loop() {
	bool event[3];

	while (1) {
		bzero(event, sizeof(event));
		poll_event(event);
		handle_event(event);
	}
}

void deamonize() {
	deamon_loop();
}
