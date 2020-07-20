#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#include <galileo2io.h>

int pputs(const char path[], const char s[]) {

	const int ERROR = -1;

	int fd, n;

	if ((fd=open(path,O_WRONLY)) == ERROR) {
		return ERROR;	
	} 
	n = write(fd, s, strlen(s));
	close(fd);
	
	return n;
}