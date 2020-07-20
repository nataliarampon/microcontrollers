#include <stdio.h>
#include <stdlib.h>

#include <galileo2io.h>

int main(int argc, char* argv[]) {
	int const SUCCESS = 0;
	int const CONV_MV_TO_VOLTS = 1000;
	int const ENOUGH = 80;

	char scale_str[ENOUGH], raw_value_str[ENOUGH];
	float scale, value;
	int raw_value;

	pgets(scale_str, sizeof scale_str, "/sys/bus/iio/devices/iio:device0/in_voltage0_scale");
	printf("Scale: %s\n", scale_str);
	scale = atof(scale_str)/CONV_MV_TO_VOLTS;


	for(;;) {
		pgets(raw_value_str, sizeof raw_value_str, "/sys/bus/iio/devices/iio:device0/in_voltage0_raw");
		raw_value = atoi(raw_value_str);
		value = raw_value*scale;

		printf("Raw: %d\tScale: %f\tValue: %fV\n",raw_value,scale,value);
	}

	return SUCCESS;
}