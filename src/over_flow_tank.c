#include "over_flow_tank.h"


static volatile uint32_t ofs_button_state = 0;
static volatile uint32_t fls_button_state = 0;
static volatile uint32_t nws_button_state = 0;

void init_over_flow_tank(void){
	initialize_full_tank();
	
	/*Unlocked the PA2 pin to use GPIODEN register*/
	GPIOCR_PORT_A |= 0x04U;
	
	/* Enabling the PD6 pin as output*/
	GPIODIR_PORT_D |= 0x40U;
	
	/*Enabling the PA2 as input */
	GPIODIR_PORT_A &= ~(0x01U << OFS);
	
	/*Enabling PA2, PD6 as digital*/
	GPIODEN_PORT_A |= 0x04;
	GPIODEN_PORT_D |= 0x40;
	
	/*Turning off the Red LED */
	turn_off_port_pin(&GPIODATA_PORT_D, RED_LED_OFF);
	
	/*Reading initial data from ofs button*/
	ofs_button_state = read_port_pin(&GPIODATA_PORT_A, OFS);
}

void run_over_flow_tank(void){
	nws_button_state = read_port_pin(&GPIODATA_PORT_A, NWS);
	
	if(nws_button_state == 0){ // nws = 0
		fls_button_state = read_port_pin(&GPIODATA_PORT_C, FLS);
		if(fls_button_state){ // fls = 1 Yellow led should be On
      ofs_button_state = read_port_pin(&GPIODATA_PORT_A, OFS);
			if(ofs_button_state){
				turn_off_port_pin(&GPIODATA_PORT_C, YELLOW_LED_OFF);
				turn_on_port_pin(&GPIODATA_PORT_D, RED_LED_ON);
			}
			else{
					turn_off_port_pin(&GPIODATA_PORT_D, RED_LED_OFF);
					turn_on_port_pin(&GPIODATA_PORT_C, YELLOW_LED_ON);
			}
			turn_off_port_pin(&GPIODATA_PORT_D, GREEN_LED_OFF);
		}
		else{ // nws = 0 && fws = 0 Green Led should be on
	    turn_on_port_pin(&GPIODATA_PORT_D, GREEN_LED_ON);
      turn_off_port_pin(&GPIODATA_PORT_C, YELLOW_LED_OFF);
			turn_off_port_pin(&GPIODATA_PORT_D, RED_LED_OFF);
		}
	}
	else{ // nws = 1 and fls = 0 or 1 All leds should shut down
	  turn_off_port_pin(&GPIODATA_PORT_D, GREEN_LED_OFF);
	  turn_off_port_pin(&GPIODATA_PORT_C, YELLOW_LED_OFF);
		turn_off_port_pin(&GPIODATA_PORT_D, RED_LED_OFF);
	}
	delay(10000);
}
