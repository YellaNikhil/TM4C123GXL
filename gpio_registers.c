#include<stdint.h>

#include "gpio_registers.h"


static void gpio_configure_pin_type(GPIOA_Type *PORT,uint32_t pin_no, uint32_t optype){
	PORT->DEN |= (optype << pin_no);
	PORT->DIR |= (optype << pin_no);
}


//static void gpio_configure_pin_pull(GPIOA_Type* PORT, uint32_t pin_no, uint32_t pulltype){
//	PORT->PUR &= ~(1 << pin_no);
//	PORT->PUR |= (pulltype << pin_no);
//}

void set_high_port_pin(GPIOA_Type* port, uint32_t pin_no){
	port->DATA |= (1ul << pin_no);
}

void set_low_port_pin(GPIOA_Type* port, uint32_t pin_no){
	port->DATA &= ~(1ul << pin_no);
}

void turn_on_port_pin(volatile uint32_t* PORT, uint32_t pin_no){
	(*PORT) |= (1UL << pin_no);
}

void turn_off_port_pin(volatile uint32_t* PORT, uint32_t pin_no){
	*PORT &= ~(1UL << pin_no);
}

uint8_t read_port_pin(volatile uint32_t* PORT, uint32_t pin_no){
	uint8_t val;
	uint32_t port_value = *PORT;
	val = (uint8_t)((port_value & (1 << pin_no)) >> pin_no);
	return val;
}

void init_sys_tick_timer(void){
	SYSTICK_STCTRL = 0;
	SYSTICK_STRELOAD = 0;
	SYSTICK_STCURRENT = 0;
	SYSTICK_STCTRL |= 0x05;
}


void delay(uint32_t time){
	while(time--);
}

/*Entire delay time for 1 value is approx. 2.841us i.e. 352Khz of frequency*/
void delay_us(int delay)  
{ 
	while(delay--){
		__asm("nop"); // almost 1us
	}
}

//static void delay_wait_1ms(void){
//	// beacuse the 4 operations in this function will take 4*(1/16Mhz) time 
//	SYSTICK_STRELOAD = 16000 - 4;
//	SYSTICK_STCURRENT = 0;
//	while((SYSTICK_STCTRL & 0x10000) == 0){}
//}

void delay_ms(uint32_t delay){
	while(delay--){
		delay_us(DELAY_US_1000);
	}
}

void gpio_init(GPIOA_Type* PORT, gpio_info *gpio){
	gpio_configure_pin_type(PORT, gpio->pin_no, gpio->optype);
	
	//gpio_configure_pin_pull(PORT, gpio->pin_no, gpio->pulltype);
	
}
		
