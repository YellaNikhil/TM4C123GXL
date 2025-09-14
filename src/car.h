#ifndef _CAR_H_
#define _CAR_H_

#include "l_298n_motor_driver.h"

#define FORWARD_DIRECTION HIGH
#define BACKWARD_DIRECTION LOW

typedef struct{
	motor_handler *front_left_motor;
	motor_handler *front_right_motor;
	motor_handler *back_left_motor;
	motor_handler *back_right_motor;
}car_handler;

void car_init(car_handler *car_info);
void car_move_forward(car_handler *car_info);
void car_move_backward(car_handler *car_info);
void car_move_right(car_handler *car_info);
void car_move_left(car_handler *car_info);
void stop_car(car_handler *car_info);

#endif
