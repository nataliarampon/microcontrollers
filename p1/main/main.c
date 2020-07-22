/*
  main.c: Program for the ENG10032 2020/1 First Exam
  
  Copyright (c) 2020 Natalia Gubiani Rampon <ngrampon@inf.ufrgs.br>

*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <galileo2io.h>

#define VDD 5
#define DATA_POINTS 1000
#define SAMPLING_PERIOD 1e-3
#define CONV_MV_TO_VOLTS 1000

struct sensors
{
    float rotary;
    float a4;
};

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
    Sleep for the given sampling period
    @param sampling_period: sampling period in seconds
**/
void sleep_for_sampling_period(double sampling_period) {
    printf("Sleeping for %.0lfus\n", ceil(sampling_period*1e6));
    usleep(ceil(sampling_period*1e6)); 
}

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
int write_period_to_pwm(int period, int pwm_pin) {
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

int main(int argc, char *argv[]) {

    int board;
    FILE *file;
    float scale_rotary, scale_a4;
    int raw_rotary, raw_a4;
    float duty_cycle;
    int period;
    int i;
    static struct sensors data[DATA_POINTS];

    board=board_name();

    // Check if the user is using the right version of the board
    if (board != BOARD_GALILEO_GEN1) {
        printf("You must be using a Galileo Gen1 Board to execute this program.\n");
        return -1;
    }

    if(argc != 2){
        puts("Usage: continuous <output_file>\n");
        return -1;
    }


    printf("Starting program:\n");

    scale_rotary = read_ad_scale(5);
    scale_a4 = read_ad_scale(4);

    period = frequency_to_period(1000);
    printf("%d\n", write_period_to_pwm(period, 1));
    printf("%d\n", write_duty_cycle_to_pwm(0,1));
    printf("%d\n", write_enable_to_pwm(1,1));

    sleep(2);

    for(i = 0 ; i < DATA_POINTS ; i++) {
        raw_rotary = read_ad_raw(5);
        raw_a4 = read_ad_raw(4);
        duty_cycle = (scale_rotary*raw_rotary)/VDD;
        printf("%d\n", write_duty_cycle_to_pwm_with_period(period, duty_cycle, 1));
        
        data[i].rotary = raw_rotary*scale_rotary;
        data[i].a4 = raw_a4*scale_a4;

        printf("Rotary: %d\tA4: %d\tDuty Cycle %f\n", raw_rotary, raw_a4, duty_cycle);
        
        sleep_for_sampling_period(SAMPLING_PERIOD);
    }

    if((file=fopen(argv[1],"w")) == NULL){
        perror("Opening output file:"); // maps errno to string into stderr
        return -1;
    }

    for(i = 0; i < DATA_POINTS ; i ++) {
        fprintf(file,"%f\t%f\n",
                        data[i].rotary,
                        data[i].a4);
    }

    write_enable_to_pwm(0, 1);

    return 0;
}