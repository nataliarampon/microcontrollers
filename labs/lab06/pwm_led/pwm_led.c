#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <galileo2io.h>

int frequency_to_period(int freq);

int main(int argc, char *argv[]) {

	const int SUCCESS = 0;
	int period, duty_period;
	float duty_cycle = 0;
	char period_str[15], duty_str[15];

	period = frequency_to_period(1000);
	sprintf(period_str, "%d", period);
	
	pputs("/sys/class/pwm/pwmchip0/pwm3/period", period_str);
	pputs("/sys/class/pwm/pwmchip0/pwm3/duty_cycle", "0");
	pputs("/sys/class/pwm/pwmchip0/pwm3/enable", "1");

	printf("Period in ns: %s\n", period_str);

	while (duty_cycle <= 1) {

		duty_period = (int) period*duty_cycle;
		snprintf(duty_str, sizeof(duty_str), "%d", duty_period);
		pputs("/sys/class/pwm/pwmchip0/pwm3/duty_cycle", duty_str);

		printf("Duty cycle: %.2f Duty period: %s\n", duty_cycle, duty_str);

		sleep(1);
		duty_cycle += 0.10;	// 10 percent increase
	}

	pputs("/sys/class/pwm/pwmchip0/pwm3/enable", "0");

	return SUCCESS;
}

/**
	Input: frequency in Hz
	Return: period in nanoseconds
**/
int frequency_to_period(int freq) {
	return (int) (1000000000/freq);
}