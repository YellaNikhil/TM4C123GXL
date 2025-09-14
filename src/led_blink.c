#include "led_blink.h"
#include "gpio_registers.h"

void init_led(void){
	
	RCGC_GPIO |= 0x20;
	
	GPIODEN_PORT_F |= LED_ON;
	GPIODIR_PORT_F |= LED_ON;
	GPIODATA_PORT_F &= LED_OFF;
	
	init_sys_tick_timer();
}


void blink_led(void){
	turn_on_port_pin(&GPIODATA_PORT_F, 2);
	delay_us(10);
	turn_off_port_pin(&GPIODATA_PORT_F, 2);
	delay_ms(10);
}

