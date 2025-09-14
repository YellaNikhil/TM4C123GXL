#ifndef _CAN_H_
#define _CAN_H_

#include "gpio_registers.h"

void can_init(void);
void can_transmit(uint8_t *message);



#endif