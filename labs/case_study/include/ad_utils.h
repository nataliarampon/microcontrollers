/*
  ad_utils.h: Utility functions for Galileo A/D conversor
  
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

#ifndef AD_UTILS_H
#define AD_UTILS_H

#define CONV_MV_TO_VOLTS 1000
#define LAST_12_BITS_MASK 0xfff

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

/* Four sensores data struct for Galileo */
struct sensors
{
        uint16_t a0;        /* be:u12/16>>0 */
        uint16_t a1;        /* be:u12/16>>0 */
        uint16_t a2;        /* be:u12/16>>0 */
        uint16_t a3;        /* be:u12/16>>0 */
        int64_t timestamp;  /* le:s64/64>>0 */
};

extern float read_ad_scale(int ad_pin);
extern int read_ad_raw(int ad_pin);

extern int write_enable_buffer(const char enable[]);
extern int disable_buffer();
extern int enable_buffer();
extern int write_buffer_length(int data_points);

extern int write_enable_ad_pin(int ad_pin, char const enable[]);
extern int disable_ad_pin(int ad_pin);
extern int enable_ad_pin(int ad_pin);

extern int write_to_timestamp(char const enable[]);
extern int disable_timestamp();
extern int enable_timestamp();

extern int set_current_trigger(int trigger);
extern int disable_trigger(int trigger);

extern int period_to_frequency(int period);
extern int set_trigger_frequency(int trigger, int frequency);
extern void sleep_for_total_sampling_time(int sampling_period, int data_points);

extern int trigger_sysfs(int trigger);
extern void sleep_for_sampling_period(int sampling_period);

extern int get_samples(struct sensors *data, int data_points);
extern uint16_t reverse_12_oof_16_aligned_0(uint16_t data);

#ifdef __cplusplus
};
#endif

#endif