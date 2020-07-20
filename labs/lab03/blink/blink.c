/*
  blink.c: Blinks a LED on Galileog gpio3 or Galileo Gen2 IO13.
  
  Copyright (c) 2016, 2020 Walter Fetter Lages <w.fetter@ieee.org>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

    You can also obtain a copy of the GNU General Public License
    at <http://www.gnu.org/licenses>.

*/

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
	    fd=open("/sys/class/gpio/gpio3/value",O_WRONLY);
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
