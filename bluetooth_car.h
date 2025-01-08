#ifndef _BLUETOOTH_CAR_H
#define _BLUETOOTH_CAR_H


#include "gpio_registers.h"
#include "uart.h"
#include "car.h"

void bluetooth_car_init(uart_handler* bluetooth, car_handler* car);
void bluetooth_car_run(uart_handler* bluetooth, car_handler* car);

#endif
