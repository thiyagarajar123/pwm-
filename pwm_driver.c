#include "pwm_driver.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

void pwm_init_pin(uint gpio, uint slice_num, uint channel, uint freq, float duty_cycle) {
    gpio_set_function(gpio, GPIO_FUNC_PWM);

    uint32_t clock = clock_get_hz(clk_sys);
    uint32_t divider16 = clock / freq / 4096 + (clock % (freq * 4096) != 0); // use 12-bit resolution
    if (divider16 / 16 == 0) divider16 = 16;

    pwm_set_clkdiv_int_frac(slice_num, divider16 / 16, divider16 & 0xF);
    pwm_set_wrap(slice_num, 4095);

    pwm_set_chan_level(slice_num, channel, duty_cycle * 4095.0f);
    pwm_set_enabled(slice_num, true);
}

void pwm_set_duty(uint slice_num, uint channel, float duty_cycle) {
    if (duty_cycle < 0.0f) duty_cycle = 0.0f;
    if (duty_cycle > 1.0f) duty_cycle = 1.0f;
    pwm_set_chan_level(slice_num, channel, duty_cycle * 4095.0f);
}

void pwm_enable(uint slice_num) {
    pwm_set_enabled(slice_num, true);
}

void pwm_disable(uint slice_num) {
    pwm_set_enabled(slice_num, false);
}
