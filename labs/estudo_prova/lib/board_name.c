#include <fcntl.h>	// file control options (O_RDONLY, etc)
#include <string.h> // strncmp
#include <unistd.h> // I/O primitives (open/read)

#include <galileo2io.h>

int board_name(void) {

	const int BOARD_VERSION_STRING_LENGTH = 20;
	const char GALILEO_GEN1_ID_STR[8] = "Galileo";
	const char GALILEO_GEN2_ID_STR[12] = "GalileoGen2";

	int fd, n;
	char s[BOARD_VERSION_STRING_LENGTH];

	fd = open("/sys/devices/virtual/dmi/id/board_name", O_RDONLY);
	n = read(fd, s, sizeof s);
	close(fd);
	s[n-1]='\0'; // discards new line

	if (strncmp(s, GALILEO_GEN1_ID_STR, sizeof s) == 0) {
		return BOARD_GALILEO_GEN1;
	} else if (strncmp(s, GALILEO_GEN2_ID_STR, sizeof s) == 0) {
		return BOARD_GALILEO_GEN2;
	} else return BOARD_UNKNOWN;
}