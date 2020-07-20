/*
  ad_utils.c: Utility functions for Galileo A/D conversor
  
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

#include <ad_utils.h>

#include <galileo2io.h>
#include <stdio.h>
#include <stdlib.h>

/**
	Read the scale to Volts for a given A/D pin
	@param ad_pin: the A/D pin to read from
	@return: the scale
**/
float read_ad_scale(int ad_pin) {
	char data_str[80], file_str[80];
	snprintf(file_str, sizeof file_str, "/sys/bus/iio/devices/iio:device0/in_voltage%d_scale", ad_pin);
	pgets(data_str, sizeof data_str, file_str);
	return atof(data_str)/CONV_MV_TO_VOLTS;
}