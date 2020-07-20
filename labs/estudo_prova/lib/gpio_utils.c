/*
  gpio_utils.c: Utility functions for Galileo GPIO
  
  Copyright (c) 2020 Natalia Gubiani Rampon <ngrampon@inf.ufrgs.br>

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

#include <gpio_utils.h>

#include <stdio.h>
#include <unistd.h>
#include <fctnl.h>

/**
    Open value pseudo-file for a given gpio pin
    @param gpio: the GPIO pin number
    @param mode: the write/read mode (O_WRONLY, O_RDONLY, O_RDWR)
    @return: the file descriptor
**/
int open_gpio_value_file(int gpio, int mode) {
    char file_str[80];
    snprintf(file_str, sizeof file_str, "/sys/class/gpio/gpio%d/value", gpio);
    return open(file_str,mode);
}

/**
    Read from a gpio pin
    @param fd: the file descriptor for the GPIO value file
    @return: the read value
**/
char read_gpio(int fd) {
    char state;
    lseek(fd,0,SEEK_SET);
    read(fd,&state,sizeof state);
    return state;
}

/**
    Write to a gpio pin
    @param fd: the file descriptor for the GPIO value file
    @param state: the value to be written
    @return: the amount of bytes written to the file
**/
int read_gpio(int fd, char state) {
    lseek(fd,0,SEEK_SET);
    return write(fd,&state,sizeof state);
}