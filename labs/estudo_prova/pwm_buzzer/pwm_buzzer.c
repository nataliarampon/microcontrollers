/*
  pwm_buzzer.c: Controls a buzzer frequency with PWM by using a potentiometer
  				in single-fire mode
  
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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include <galileo2io.h>
#include <pwm_utils.h>

#define VDD 5
#define CONV_MV_TO_VOLTS 1000;

int main(int argc, char *argv[]) {

	int period, raw_value;
	float scale, value, duty_cycle;
	char data_str[40];

	period = frequency_to_period(1000);
	snprintf(data_str, sizeof data_str, "%d", period);
	
	pputs("/sys/class/pwm/pwmchip0/pwm3/period", data_str);
	pputs("/sys/class/pwm/pwmchip0/pwm3/duty_cycle", "0");

	pgets(data_str, sizeof data_str, "/sys/bus/iio/devices/iio:device0/in_voltage0_scale");
	scale = atof(data_str)/CONV_MV_TO_VOLTS;

	pputs("/sys/class/pwm/pwmchip0/pwm3/enable", "1");

	for(;;) {

		pgets(data_str, sizeof data_str, "/sys/bus/iio/devices/iio:device0/in_voltage0_raw");
		raw_value = atoi(data_str);
		value = raw_value*scale;
		duty_cycle = value/VDD;

		snprintf(data_str, sizeof data_str, "%d", (int) round(period*duty_cycle));
		pputs("/sys/class/pwm/pwmchip0/pwm3/duty_cycle", data_str);

		printf("Duty cycle: %.3f\n", duty_cycle);
		printf("Raw: %d\tScale: %.3f\tValue: %.3fV\n", raw_value, scale, value);
	}

	pputs("/sys/class/pwm/pwmchip0/pwm3/enable", "0");

	return 0;
}