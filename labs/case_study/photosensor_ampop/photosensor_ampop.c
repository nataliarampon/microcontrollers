#include <stdio.h>

#include <galileo2io.h>
#include <ad_utils.h>

#define DATA_POINTS 1024
#define SAMPLING_PERIOD 1e-3 

int main(int argc, char *argv[]) {

	float scale;
	int i;
	int samples;
	static struct sensors data[DATA_POINTS];

	printf("%d\n", disable_buffer());
	scale = read_ad_scale(0);
	printf("%d\n", enable_ad_pin(0));
	printf("%d\n", enable_timestamp());
	printf("%d\n", write_buffer_length(DATA_POINTS));

#ifdef TRIG_SYSFS
	set_current_trigger(0);
#else
	printf("%d\n", set_current_trigger(1));
	printf("%d\n", set_trigger_frequency(1,period_to_frequency(SAMPLING_PERIOD)));
#endif

	printf("%d\n", enable_buffer());

#ifdef TRIG_SYSFS
	for(i=0; i < DATA_POINTS;i++) {
        trigger_sysfs(0);
        sleep_for_sampling_period(SAMPLING_PERIOD);
    }
#else
	sleep_for_total_sampling_time(SAMPLING_PERIOD, DATA_POINTS);
#endif

	printf("%d\n", disable_buffer());
	printf("%d\n", disable_trigger());
	samples = get_samples(data, DATA_POINTS);
	printf("Number of samples: %d\n", samples);

	write_buffer_length(2);
	disable_ad_pin(0);
	disable_timestamp();

	for(i = 0; i < samples; i ++) {
		printf("%f\t%f\t\n", reverse_12_oof_16_aligned_0(data[i].a0)*scale, (data[i].timestamp-data[0].timestamp)*1e9);
	}

	return 0;
}