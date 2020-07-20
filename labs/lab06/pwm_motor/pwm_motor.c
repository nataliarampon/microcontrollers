#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include <galileo2io.h>

int frequency_to_period(int freq);

int main(int argc, char *argv[]) {

	const int SUCCESS = 0;
	const int ERROR = -1;

	const int MAX_DUTY_PERIOD = 1000000;		// 1ms
	const int NEUTRAL_POINT_PERIOD = 1500000; 	// 1,5ms
	const int PWM_FREQ_FOR_SERVO_MOTOR = 50;	// 50Hz

	int period, duty_period, angle_in_deg, angle_in_rads;
	char period_str[15], duty_str[15];

	period = frequency_to_period(PWM_FREQ_FOR_SERVO_MOTOR);
	sprintf(period_str, "%d", period);

	if (argc < 2) {
		printf("Usage: %s <angle>\n", argv[0]);
		return ERROR;
	}

	angle_in_deg = atoi(argv[1]);
	angle_in_rads = angle_in_deg * M_PI/180.0;

	if ((angle_in_rads < -M_PI_2) || (angle_in_rads > M_PI_2)) {
		printf("Acceptable angles are between -90 and 90 degrees.\n");
		return ERROR;
	}

	duty_period = (angle_in_rads/M_PI_2)*MAX_DUTY_PERIOD + NEUTRAL_POINT_PERIOD;
	snprintf(duty_str, sizeof(duty_str), "%d", duty_period);
	
	pputs("/sys/class/pwm/pwmchip0/pwm3/period", period_str);
	pputs("/sys/class/pwm/pwmchip0/pwm3/duty_cycle", duty_str);
	pputs("/sys/class/pwm/pwmchip0/pwm3/enable", "1");

	sleep(1);	// Let's pretend there's a motor moving here

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