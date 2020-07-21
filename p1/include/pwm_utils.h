/*
  pwm_utils.h: Utility functions for Galileo PWM usage
  
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

#ifndef PWM_UTILS_H
#define PWM_UTILS_H

#ifdef __cplusplus
extern "C"
{
#endif

extern int frequency_to_period(int freq);
extern int write_period_to_pwm(int period, int pwm_pin);
extern int write_enable_to_pwm(int enable, int pwm_pin);
extern int write_duty_cycle_to_pwm(int duty_cycle, int pwm_pin);
extern int write_duty_cycle_to_pwm_with_period(int period, float duty_cycle, int pwm_pin);

#ifdef __cplusplus
};
#endif

#endif