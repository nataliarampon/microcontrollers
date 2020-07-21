#include <stdio.h>
#include <unistd.h>
#include <galileo2io.h>
#include <pwm_utils.h>
#include <ad_utils.h>

#define VDD 5

int main(int argc, char *argv[]) {

	float scale;
	int raw;
	float duty_cycle;
	int period;

	scale = read_ad_scale(0);
	period = frequency_to_period(1000);

	write_period_to_pwm(period, 3);
	write_duty_cycle_to_pwm(0,3);
	write_enable_to_pwm(1, 3);

	for(;;) {
		raw = read_ad_raw(0);

		// the duty_cycle is how the rotary voltage 
		// compares to the maximum voltage
		duty_cycle = (scale*raw)/VDD;
		printf("Raw: %d\tValue:%f\tDuty_cycle: %f\n", raw, scale*raw, duty_cycle);
		printf("%d\n", write_duty_cycle_to_pwm_with_period(period, duty_cycle, 3));
	}

	write_enable_to_pwm(0, 3);

	return 0;
}