/*
  int_utils.c: Utility functions for Galileo interruptions
  
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

#include <int_utils.h>

#include <galileo2io.h>
#include <gpio_utils.h>
#include <unistd.h>
#include <stdio.h>
#include <poll.h>
#include <fcntl.h>

/**
	Configures interruption edge to given GPIO pin
	@param gpio: number of the GPIO pin
	@param edge: edge type to be written ("rising", "falling" or "none")
	@return: number of bytes written to file
**/
int write_int_edge(int gpio, const char edge[]) {
	char file_str[80];
	snprintf(file_str, sizeof file_str, "/sys/class/gpio/gpio%d/edge", gpio);
	return pputs(file_str, edge);
}

/**
	Configures interruption rising edge to given GPIO pin
	@param gpio: number of the GPIO pin
	@return: number of bytes written to file
**/
int config_rising_edge(int gpio) {
	return write_int_edge(gpio, "rising");
}

/**
	Configures interruption falling edge to given GPIO pin
	@param gpio: number of the GPIO pin
	@return: number of bytes written to file
**/
int config_falling_edge(int gpio) {
	return write_int_edge(gpio, "falling");
}

/**
	Disables interruption detection in GPIO pin
	@param gpio: number of the GPIO pin
	@return: number of bytes written to file
**/
int disable_interruption(int gpio) {
	return write_int_edge(gpio, "none");
}

/**
	Polls for interruption on the given GPIO pin
	Pre-condition: GPIO must be previously configured with falling or rising edge
	@param gpio: number of the GPIO pin
	@return: state of the GPIO pin
**/
unsigned char poll_for_interruption(int gpio) {
	unsigned char state;
	struct pollfd pfd;

	pfd.fd = open_gpio_value_file(gpio, O_RDONLY);

	if (pfd.fd < 0) {
		perror("Opening gpio:");
		return -1;
	}

	read(pfd.fd, &state, 1); // Clear old values
	pfd.events=POLLPRI;

	poll(&pfd, 1, -1);

	lseek(pfd.fd, 0 , SEEK_SET);
	read(pfd.fd, &state, 1);

	close(pfd.fd);
	return state;
}