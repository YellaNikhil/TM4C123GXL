#ifndef JOYSTICK_H
#define JOYSTICK_H

#include<stdint.h>
#include<TM4C123GH6PM.h>

void init_joystick_ports(void);
void run_joystick(void);
uint32_t read_joystick(void);

#endif
