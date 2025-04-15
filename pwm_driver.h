#ifndef PWM_DRIVER_H
#define PWM_DRIVER_H

#include "pico/stdlib.h"

void pwm_init_pin(uint gpio, uint slice_num, uint channel, uint freq, float duty_cycle);
void pwm_set_duty(uint slice_num, uint channel, float duty_cycle);
void pwm_enable(uint slice_num);
void pwm_disable(uint slice_num);

#endif
