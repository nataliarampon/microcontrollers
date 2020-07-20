#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#include <galileo2io.h>

int pputs(const char path[], const char s[]) {

	const int ERROR = -1;

	int fd, n;

	if ((fd=open(path,O_WRONLY)) == ERROR){
		printf("ERROR in pputs: couldn't open file %s\n", path);
		return ERROR;	
	} 
	n = write(fd, s, strlen(s));
	printf("SUCCESS in pputs: Wrote %d bytes (%s) to %s\n", n, s, path);
	close(fd);
	
	return n;
}