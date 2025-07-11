#ifndef _ULTRASONIC_H
#define _ULTRASONIC_H

#include "gpio_registers.h"

extern volatile uint32_t time_travelled;
extern volatile uint32_t rising_time, falling_time;

void ultrasonic_init(gpio_info *echo_pin, gpio_info *trigger_pin);
uint32_t measure_distance(gpio_info *, TIMER0_Type *);

#endif
