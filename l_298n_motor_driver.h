#ifndef _L_298_DRIVER_H_
#define _L_298_DRIVER_H_


#include "gpio_registers.h"


typedef struct{
		gpio_info *low_pin;
		gpio_info *high_pin;
		gpio_info *pwm_pin;
		PWM0_Type *pwm;
		uint32_t pwm_type;
		uint32_t speed;
		uint32_t direction;
}motor_handler;

void motor_init(motor_handler *motor);
void move_forward(motor_handler *motor);
void move_backward(motor_handler *motor);
void stop_movement(motor_handler *motor);

#endif
