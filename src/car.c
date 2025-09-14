#include "car.h"
#include "l_298n_motor_driver.h"

void car_init(car_handler *car_info){
		motor_init(car_info->front_left_motor);
		motor_init(car_info->front_right_motor);
		motor_init(car_info->back_left_motor);
		motor_init(car_info->back_right_motor);
}

void car_move_forward(car_handler *car_info){
		move_forward(car_info->front_left_motor);
		move_forward(car_info->front_right_motor);
		move_forward(car_info->back_left_motor);
		move_forward(car_info->back_right_motor);
}

void car_move_backward(car_handler *car_info){
		move_backward(car_info->front_left_motor);
		move_backward(car_info->front_right_motor);
		move_backward(car_info->back_left_motor);
		move_backward(car_info->back_right_motor);
}

void car_move_right(car_handler *car_info){
		stop_movement(car_info->front_right_motor);
		move_forward(car_info->front_left_motor);
		move_forward(car_info->back_left_motor);
		move_forward(car_info->back_right_motor);
}

void car_move_left(car_handler *car_info){
		stop_movement(car_info->front_left_motor);
		move_forward(car_info->front_right_motor);
		move_forward(car_info->back_left_motor);
		move_forward(car_info->back_right_motor);
}

void stop_car(car_handler *car_info){
	stop_movement(car_info->front_left_motor);
	stop_movement(car_info->front_right_motor);
	stop_movement(car_info->back_left_motor);
	stop_movement(car_info->back_right_motor);
}
