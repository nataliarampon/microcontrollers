#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
	char state='0';
	int fd;
	char s[20];
	int n;
	
	fd=open("/sys/devices/virtual/dmi/id/board_name",O_RDONLY);
	n=read(fd,s,sizeof s);
	close(fd);
	s[n-1]='\0'; /* Discards new line */

	if(strncmp(s,"Galileo",sizeof s) == 0)
	    fd=open("/sys/class/gpio/gpio18/value",O_WRONLY);
	else if(strncmp(s,"GalileoGen2",sizeof s) == 0)
	    fd=open("/sys/class/gpio/gpio7/value",O_WRONLY);
        else return -1;

	for(;;)
	{	
		lseek(fd,0,SEEK_SET);
		write(fd,&state,sizeof state);
		sleep(1);
		state^='0'^'1';
	}
	
	close(fd);
	
	return 0;
}
