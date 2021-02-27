#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <libinput.h>
#include <libudev.h>
#include <stdio.h>
#include <unistd.h>


static int open_restricted(const char* path, int flags, void* user_data)
{
	int fd = open(path, flags);
	return fd < 0 ? -errno : fd;
}

static void close_restricted(int fd, void* user_data)
{
	close(fd);
}

const static struct libinput_interface interface = {
	.open_restricted = open_restricted,
	.close_restricted = close_restricted,
};

void handle_device_added(struct libinput_event_device_notify* event)
{
	assert(event != NULL);
}

void handle_button_press(struct libinput_event_switch* event)
{
	assert(event != NULL);


}

int main(int argc, char* argv[])
{
	struct udev* udev_context = udev_new();
	struct libinput* libinput_context = libinput_udev_create_context(&interface, NULL, udev_context);

	libinput_udev_assign_seat(libinput_context, "seat0");

	int libinput_fd = libinput_get_fd(libinput_context);

	struct libinput_event* event;

	// Setup loop
	libinput_dispatch(libinput_context);
	while ((event = libinput_get_event(libinput_context)) != NULL) {
		printf("Setup event occurred\n");

		if (libinput_event_get_type(event) == LIBINPUT_EVENT_DEVICE_ADDED) {
			handle_device_added(libinput_event_get_device_notify_event(event));
			printf("\tDevice added event\n");
		}
		else {
			printf("\tOther type of event\n");
		}

		libinput_event_destroy(event);
	}
	printf("No more setup events\n");

	// Main loop
	while (1) {
		// TODO: use select/poll/epoll to block until fd has new data
		// https://daniel.haxx.se/docs/poll-vs-select.html
		// https://en.wikipedia.org/wiki/Epoll
		// https://github.com/wayland-project/libinput/blob/master/tools/libinput-debug-events.c
		// https://wayland.freedesktop.org/libinput/doc/latest/api/

		libinput_dispatch(libinput_context);
		while ((event = libinput_get_event(libinput_context)) != NULL) {
			printf("Event occurred\n");

			if (libinput_event_get_type(event) == LIBINPUT_EVENT_SWITCH_TOGGLE) {
				handle_button_press(libinput_event_get_switch_event(event));
				printf("\tSwitch toggle event\n");
			}
			else {
				printf("\tOther type of event\n");
			}

			libinput_event_destroy(event);
			libinput_dispatch(libinput_context);
		}
	}

	printf("No more events\n");

	return EXIT_SUCCESS;
}
