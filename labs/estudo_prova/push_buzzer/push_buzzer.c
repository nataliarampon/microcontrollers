#include <fcntl.h>
#include <poll.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#include <galileo2io.h>

static volatile int run=1;

void quit(int signal)
{
        run=0;
}

int main(int argc, char *argv[]) {

	unsigned char c;
	struct pollfd pfd;
	int i;
    struct sigaction act;
    char data_str[40];

	pfd.fd = open("/sys/class/gpio/gpio15/value", O_RDONLY);

	if (pfd.fd < 0) {
		perror("Opening gpio:");
		return -1;
	}

	// Clear old values
	read(pfd.fd, &c, 1);

	pfd.events=POLLPRI;

	act.sa_handler=quit;
    sigaction(SIGINT,&act,NULL);
    sigaction(SIGTERM,&act,NULL);

	for(i=0;run;i++) {

		puts("Waiting for interrupt... Press ^C to abort");

		// gpio14 => SoC (for interruptions) in IO2
		pputs("/sys/class/gpio/gpio14/edge", "rising");

		poll(&pfd, 1, -1);

		lseek(pfd.fd, 0 , SEEK_SET);
		read(pfd.fd, &c, 1);

		data_str[0] = c;
		data_str[1] = '\0';
		// write in buzzer connected to IO3
		pputs("/sys/class/gpio/gpio15/value", data_str);

		printf("Number of interrupts: %d\n",i);
	}

	pputs("/sys/class/gpio/gpio14/edge", "none");

	close(pfd.fd);

	return 0;
}