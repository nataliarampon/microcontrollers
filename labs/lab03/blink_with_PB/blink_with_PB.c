#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc,char *argv[])
{
	char state='0';
	int fd, file_pb;
	char s[20];
	int n;
	
	fd=open("/sys/devices/virtual/dmi/id/board_name",O_RDONLY);
	n=read(fd,s,sizeof s);
	close(fd);
	s[n-1]='\0'; /* Discards new line */

	if(strncmp(s,"Galileo",sizeof s) == 0) {
	    fd=open("/sys/class/gpio/gpio18/value",O_WRONLY);
		file_pb=open("/sys/class/gpio/gpio32/value",O_RDONLY);
	} else if(strncmp(s,"GalileoGen2",sizeof s) == 0)
	    fd=open("/sys/class/gpio/gpio7/value",O_WRONLY);
        else return -1;

	for(;;)
	{	
		printf("state b4: %c\n", state);
		lseek(file_pb,0,SEEK_SET);
		read(file_pb,&state,sizeof state);
		printf("state after: %c\n", state);
		lseek(fd,0,SEEK_SET);
		write(fd,&state,sizeof state);
	}
	
	close(fd);
	
	return 0;
}
