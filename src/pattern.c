#include "pattern.h"

static volatile uint8_t button_state = 0;
	
void init_pattern_ports(void){
	RCGC_GPIO |= 0x05;
	delay(100);
	
	/*Digital enabled the pins */
	GPIODEN_PORT_A |= (1 << BUTTON);
	GPIODEN_PORT_C |= (GREEN_LED_ON | RED_LED_ON | YELLOW_LED_ON | BLUE_LED_ON);
	
	/*Enabled the leds pins as outputs and button as input */
	GPIODIR_PORT_A = 0x00;
	GPIODIR_PORT_C |= (GREEN_LED_ON | RED_LED_ON | YELLOW_LED_ON | BLUE_LED_ON);
	
	/*Initially set every led to low */
	GPIODATA_PORT_C = 0x00;
}

static void start_leds(void){
	turn_off_port_pin(&GPIODATA_PORT_C, 0x00U);
	turn_on_port_pin(&GPIODATA_PORT_C, PATTERN_1);
	delay(DELAY_20MS);
	
	turn_off_port_pin(&GPIODATA_PORT_C, PATTERN_1);
	turn_on_port_pin(&GPIODATA_PORT_C, PATTERN_2);
	delay(DELAY_20MS);
	
	turn_off_port_pin(&GPIODATA_PORT_C, PATTERN_2);
	turn_on_port_pin(&GPIODATA_PORT_C, PATTERN_3);
	delay(DELAY_20MS);
	
	turn_off_port_pin(&GPIODATA_PORT_C, PATTERN_3);
	turn_on_port_pin(&GPIODATA_PORT_C, PATTERN_4);
	delay(DELAY_20MS);
}

static void turn_off_all_leds(void){
	turn_off_port_pin(&GPIODATA_PORT_C, GREEN_LED_OFF);
	turn_off_port_pin(&GPIODATA_PORT_C, RED_LED_OFF);
	turn_off_port_pin(&GPIODATA_PORT_C, YELLOW_LED_OFF);
	turn_off_port_pin(&GPIODATA_PORT_C, BLUE_LED_OFF);
}


void run_pattern(void){
	button_state = read_port_pin(&GPIODATA_PORT_A, BUTTON);
	if(button_state){
		start_leds();
	}
	else{
		turn_off_all_leds();
	}
	delay(1000);
}
