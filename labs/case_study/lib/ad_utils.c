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
#include <unistd.h>
#include <math.h>

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

/**
	Read the raw value for a given A/D pin
	@param ad_pin: the A/D pin to read from
	@return: the raw value
**/
int read_ad_raw(int ad_pin) {
	char data_str[80], file_str[80];
	snprintf(file_str, sizeof file_str, "/sys/bus/iio/devices/iio:device0/in_voltage%d_raw", ad_pin);
	pgets(data_str, sizeof data_str, file_str);
	return atoi(data_str);
}


/**
    Writes the given value to the buffer enable pseudo-file
    @param enable: value (in a string) to be written
    @return: number of bytes written to the file
**/
int write_enable_buffer(const char enable[]) {
    return pputs("/sys/bus/iio/devices/iio:device0/buffer/enable", enable);
}

/**
    Disables A/D continuous buffer
    @return: number of bytes written to the file
**/
int disable_buffer() {
    return write_enable_buffer("0");
}

/**
    Enables A/D continuous buffer
    @return: number of bytes written to the file
**/
int enable_buffer() {
    return write_enable_buffer("1");
}

/**
    Writes the given value to the voltage enable pseudo-file of the AD pin
    @param ad_pin: number of the ad pin
    @param enable: value (in a string) to be written
    @return: number of bytes written to the file
**/
int write_enable_ad_pin(int ad_pin, char const enable[]) {
    char file_str[80];
    snprintf(file_str, sizeof file_str, "/sys/bus/iio/devices/iio:device0/scan_elements/in_voltage%d_en", ad_pin);
    return pputs(file_str, enable);
}

/**
    Disables given AD pin
    @param ad_pin: number of the ad pin
    @return: number of bytes written to the file
**/
int disable_ad_pin(int ad_pin) {
    return write_enable_ad_pin(ad_pin, "0");
}

/**
    Enables given AD pin
    @param ad_pin: number of the ad pin
    @return: number of bytes written to the file
**/
int enable_ad_pin(int ad_pin) {
    return write_enable_ad_pin(ad_pin, "1");
}

/**
    Writes the given value to the timestamp pseudo-file
    @param enable: value (in a string) to be written
    @return: number of bytes written to the file
**/
int write_to_timestamp(char const enable[]) {
    return pputs("/sys/bus/iio/devices/iio:device0/scan_elements/in_timestamp_en", enable);
}

/**
    Disables timestamp
    @return: number of bytes written to the file
**/
int disable_timestamp() {
    return write_to_timestamp("0");
}

/**
    Enables timestamp
    @return: number of bytes written to the file
**/
int enable_timestamp() {
    return write_to_timestamp("1");
}

/**
    Writes the given number of data points as the length of the A/D buffer
    @param data_points: number of data points for the length of the buffer
    @return: number of bytes written to the file
**/
int write_buffer_length(int data_points) {
    char data_str[80];
    snprintf(data_str, sizeof data_str, "%d", data_points);
    return pputs("/sys/bus/iio/devices/iio:device0/buffer/length",data_str);
}

/**
    Sets the trigger as the current trigger
    @param trigger: trigger number
    @return: number of bytes written to the current_trigger pseudo-file
**/
int set_current_trigger(int trigger) {
    char data_str[80], file_str[80];
    snprintf(file_str, sizeof file_str, "/sys/bus/iio/devices/trigger%d/name", trigger);
    pgets(data_str,sizeof data_str,file_str);
    return pputs("/sys/bus/iio/devices/iio:device0/trigger/current_trigger",data_str);
}

/**
    Converts a period in seconds to a frequency in Hz
    E.g.: to convert a sampling period into a sampling frequency
    @param period: period in seconds
    @return: frequency in Hz
**/
int period_to_frequency(int period) {
    return (int) round(1.0/period);
}

/**
    Sets the sampling frequency for a trigger
    @param trigger: trigger number
    @param frequency: the frequency in Hz
    @return: number of bytes written to the frequency pseudo-file
**/
int set_trigger_frequency(int trigger, int frequency) {
    char data_str[80], file_str[80];
    snprintf(file_str, sizeof file_str, "/sys/bus/iio/devices/trigger%d/frequency", trigger);
    snprintf(data_str, sizeof data_str, "%d", frequency);
    return pputs(file_str,data_str);
}

/**
    Trigger the sysfs trigger
    @param trigger: trigger number
    @return: number of bytes written to the trigger_now pseudo-file
**/
int trigger_sysfs(int trigger) {
    char file_str[80];
    snprintf(file_str, sizeof file_str, "/sys/bus/iio/devices/trigger%d/trigger_now", trigger);
    return pputs(file_str,"1");
}

/**
    Sleep for the given sampling period
    @param sampling_period: sampling period in seconds
**/
void sleep_for_sampling_period(int sampling_period) {
    usleep(ceil(sampling_period*1e6)); 
}

/**
    Sleep for the total sampling time
    @param sampling_period: sampling period in seconds
    @param data_points: number of data_points
**/
void sleep_for_total_sampling_time(int sampling_period, int data_points) {
    sleep(ceil(data_points*sampling_period));
}