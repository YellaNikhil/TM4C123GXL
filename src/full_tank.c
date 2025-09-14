#include "full_tank.h"

static volatile uint8_t nws_button_state = 0;
static volatile uint8_t fls_button_state = 0;



void initialize_full_tank(void){
    /*Initialize clock for PORT A, C & D*/
	RCGC_GPIO |= (0x0DU);
	delay(1000); /* Wait for clock */
	
	/* Unlock the port to use GPIODEN & GPIOCR */
	GPIOLOCK_PORT_D |= GPIOUNLOCK;
  GPIOLOCK_PORT_A |= GPIOUNLOCK;

	/* Removed the default functionality of PD7, PA5 pin and to use GPIODEN */	
	GPIOCR_PORT_D |= 0x80U;
  GPIOCR_PORT_A |= 0x40U;
	
	/* PD7, PC7 are set as outputs */
  GPIODIR_PORT_C |= 0x80U;
  GPIODIR_PORT_D |= 0x80U;

  /*PC6, PA5 are set as inputs*/
  GPIODIR_PORT_A &= (~(0x01U << NWS));
	GPIODIR_PORT_C &= (~(0x01U << FLS));

	/* PF0 - PF5 are digital enabled */
	GPIODEN_PORT_A |= 0x20U;
  GPIODEN_PORT_C |= 0xC0U;
  GPIODEN_PORT_D |= 0x80U;
	
	
	/* Turn off all leds at first stage */
	turn_off_port_pin(&GPIODATA_PORT_D, GREEN_LED_OFF);
	turn_off_port_pin(&GPIODATA_PORT_C, YELLOW_LED_OFF);
	
  /*Reading the inputs from the push buttons*/
  nws_button_state = read_port_pin(&GPIODATA_PORT_A, NWS);
	fls_button_state = read_port_pin(&GPIODATA_PORT_C, FLS);
}	

void run_full_tank(void){
	nws_button_state = read_port_pin(&GPIODATA_PORT_A, NWS);
	
	if(nws_button_state == 0){ // nws = 0
		fls_button_state = read_port_pin(&GPIODATA_PORT_C, FLS);
		if(fls_button_state){ // fls = 1 Yellow led should be On
      turn_off_port_pin(&GPIODATA_PORT_D, GREEN_LED_OFF);
	    turn_on_port_pin(&GPIODATA_PORT_C, YELLOW_LED_ON);
		}
		else{ // nws = 0 && fws = 0 Green Led should be on
	    turn_on_port_pin(&GPIODATA_PORT_D, GREEN_LED_ON);
      turn_off_port_pin(&GPIODATA_PORT_C, YELLOW_LED_OFF);
		}
	}
	else{ // nws = 1 and fls = 0 or 1 All leds should shut down
	  turn_off_port_pin(&GPIODATA_PORT_D, GREEN_LED_OFF);
	  turn_off_port_pin(&GPIODATA_PORT_C, YELLOW_LED_OFF);
	}
	delay(10000);
}


	
