#include <fcntl.h>
#include <poll.h>
#include <stdio.h>
#include <unistd.h>

#include <galileo2io.h>

int main(int argc, char *argv[]) {

	const int ERROR = -1;
	const int SUCCESS = 0;

	unsigned char c;
	struct pollfd pfd;
	int board;
	int int_count = 0;

	board=board_name();

	if (board == BOARD_GALILEO_GEN1) {
		pfd.fd = open("/sys/class/gpio/gpio15/value", O_RDONLY);
	} else if (board == BOARD_GALILEO_GEN2) {
		pfd.fd = open("/sys/class/gpio/gpio6/value", O_RDONLY);
	} else {
		pfd.fd = ERROR;
	}

	if (pfd.fd < SUCCESS) {
		perror("Opening gpio:");
		return ERROR;
	}

	// Clear old values
	read(pfd.fd, &c, 1);

	pfd.events=POLLPRI;

	if (board == BOARD_GALILEO_GEN1) {
		/**
			// gpio15 => SoC (for interruptions) in IO3
			// gpio18 => Cypress (for digital I/O) in IO3
		**/
		pputs("/sys/class/gpio/gpio15/edge", "falling");
	} else if (board == BOARD_GALILEO_GEN2) {
		pputs("/sys/class/gpio/gpio6/edge", "both");
	}

	for(;;) {
		printf("Waiting for interrupt... Count falling: %d\n", int_count);

		poll(&pfd, 1, -1);

		printf("GOTCHA!\n");

		lseek(pfd.fd, 0 , SEEK_SET);
		read(pfd.fd, &c, 1);

		int_count++;

	}

	if ( board == BOARD_GALILEO_GEN1) {
		pputs("/sys/class/gpio/gpio15/edge", "none");
	} else if (board == BOARD_GALILEO_GEN2) {
		pputs("/sys/class/gpio/gpio6/edge", "none");
	}

	close(pfd.fd);

	return SUCCESS;
}