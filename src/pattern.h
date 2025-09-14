#ifndef PATTERN_H
#define PATTERN_H

#include "gpio_registers.h"


/* LEDS are connected to PC4, PC, PC6, PC7 */
#define GREEN_LED 4
#define YELLOW_LED 5
#define RED_LED 6
#define BLUE_LED 7

/*Button is connected to PA5*/
#define BUTTON 5

#define GREEN_LED_ON (1u << GREEN_LED)
#define GREEN_LED_OFF ~(GREEN_LED_ON)

#define YELLOW_LED_ON (1u << YELLOW_LED)
#define YELLOW_LED_OFF ~(YELLOW_LED_ON)

#define RED_LED_ON (1u << RED_LED)
#define RED_LED_OFF ~(RED_LED_ON)

#define BLUE_LED_ON (1u << BLUE_LED)
#define BLUE_LED_OFF ~(BLUE_LED_ON)


/*Patterns*/
#define PATTERN_1 0x50 
#define PATTERN_2 0x60
#define PATTERN_3 0xA0
#define PATTERN_4 0x90

#define DELAY_20MS 40000

void init_pattern_ports(void);
void run_pattern(void);


#endif
