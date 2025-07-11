#include<TM4C123GH6PM.h>
#include "seven_segment_display.h"

// static volatile uint32_t sw1_state = 0, sw2_state = 0, sw3_state = 0, sw4_state = 0;

void init_ports(void){
	SYSCTL->RCGCGPIO = 0x00;
}

void run_seven_segment_display(void){}

