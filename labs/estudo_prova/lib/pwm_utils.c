/*
  pwm_utils.c: Utility functions for Galileo PWM usage
  
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
#include <pwm_utils.h>
#include <galileo2io.h>

#include <math.h>
#include <stdio.h>

/**
	Converts a period in ns to a frequency in Hz
	@param freq: frequency in Hz
	@return: period in nanoseconds
**/
int frequency_to_period(int freq) {
	return (int) round(1000000000/freq);
}

/**
    Writes a period in nanoseconds to a pwm pin period pseudo-file
    @param period: the period in nanoseconds
    @param pwm_pin: the number of the pwm pin
    @return: the number of bytes written to the pwm pin period pseudo-file
**/
int write_period_to_pwm_(int period, int pwm_pin) {
    char data_str[80], file_str[80];
    snprintf(data_str, sizeof data_str, "%d", period);
    snprintf(file_str, sizeof file_str, "/sys/class/pwm/pwmchip0/pwm%d/period", pwm_pin);
    return pputs(file_str, data_str);
}

/**
    Writes enable value to the pwm pin pseudo-file
    @param enable: the enable value, either 1 or 0
    @param pwm_pin: the number of the pwm pin
    @return: the number of bytes written to the pwm pin pseudo-file
**/
int write_enable_to_pwm(int enable, int pwm_pin) {
    char data_str[80], file_str[80];
    snprintf(data_str, sizeof data_str, "%d", enable);
    snprintf(file_str, sizeof file_str, "/sys/class/pwm/pwmchip0/pwm%d/enable", pwm_pin);
    return pputs(file_str, data_str);
}

/**
    Writes duty cycle period in nanoseconds to the pwm pin pseudo-file
    @param duty_cycle: duty cycle period in nanoseconds
    @param pwm_pin: the number of the pwm pin
    @return: the nunber of bytes written to the pwm pin pseudo-file
**/
int write_duty_cycle_to_pwm(int duty_cycle, int pwm_pin) {
    char data_str[80], file_str[80];
    snprintf(data_str, sizeof data_str, "%d", duty_cycle);
    snprintf(file_str, sizeof file_str, "/sys/class/pwm/pwmchip0/pwm%d/duty_cycle", pwm_pin);
    return pputs(file_str, data_str);
}


/**
    Writes duty cycle period in nanoseconds to the pwm pin pseudo-file based on
    a given pwm period and duty cycle percentage
    @parm period: pwm period of this pin in nanoseconds
    @param duty_cycle: duty cycle percentage (between 0 and 1), if outside allowed range, it's defaulted to zero
    @param pwm_pin: the number of the pwm pin
    @return: the nunber of bytes written to the pwm pin pseudo-file
**/
int write_duty_cycle_to_pwm_with_period(int period, float duty_cycle, int pwm_pin) {
    char data_str[80], file_str[80];
    if (duty_cycle < 0 || duty_cycle > 1) duty_cycle = 0;
    snprintf(data_str, sizeof data_str, "%d", (int) round(duty_cycle*period));
    snprintf(file_str, sizeof file_str, "/sys/class/pwm/pwmchip0/pwm%d/duty_cycle", pwm_pin);
    return pputs(file_str, data_str);
}