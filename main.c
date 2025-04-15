#include <stdio.h>
#include "pico/stdlib.h"
#include "pwm_driver.h"
#include "hardware/pwm.h"

#define PWM_GPIO 15  // any PWM-capable GPIO

int main() {
    stdio_init_all();

    uint slice = pwm_gpio_to_slice_num(PWM_GPIO);
    uint channel = pwm_gpio_to_channel(PWM_GPIO);

    pwm_init_pin(PWM_GPIO, slice, channel, 1000, 0.5f);  // 1kHz, 50% duty

    while (1) {
        for (float duty = 0.0f; duty <= 1.0f; duty += 0.01f) {
            pwm_set_duty(slice, channel, duty);
            sleep_ms(10);
        }
        for (float duty = 1.0f; duty >= 0.0f; duty -= 0.01f) {
            pwm_set_duty(slice, channel, duty);
            sleep_ms(10);
        }
    }
}
