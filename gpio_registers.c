#include<stdint.h>

#include "gpio_registers.h"

static void delay_wait_1ms(void);
static void delay_wait_1us(void);

/*GPIO configure functions*/
static void gpio_configure_pin_type(GPIOA_Type *, uint32_t, uint32_t);
static void gpio_configure_alternate_function(GPIOA_Type *, uint32_t, uint32_t, uint32_t);
static void gpio_configure_digital_enable(GPIOA_Type *, uint32_t, uint32_t);
static void gpio_configure_pin_pull(GPIOA_Type* PORT, uint32_t pin_no, uint32_t pulltype);

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
void delay_us(uint32_t delay)  
{ 
	while(delay--){
		delay_wait_1us();
	}
}

static void delay_wait_1us(void){
	SYSTICK_STRELOAD = 16 - 1;
	while((SYSTICK_STCTRL & 0x10000) == 0);
}


 static void delay_wait_1ms(void){
	SYSTICK_STRELOAD = 16000 - 1;
	while((SYSTICK_STCTRL & 0x10000) == 0);
}
 
 void delay_wait_1s(void){
	SYSTICK_STRELOAD = 16000000 - 4;
	while((SYSTICK_STCTRL & 0x10000) == 0);
}


void delay_ms(uint32_t delay){ 
	while(delay--){
		delay_wait_1ms();
	}
}

void gpio_init(GPIOA_Type* PORT, gpio_info *gpio){
	/*To configure the pin type to digital or not*/
	gpio_configure_digital_enable(PORT, gpio->pin_no, gpio->digital_enable);
	
	/* To configure the pin type to digital and op type to input or output*/
	gpio_configure_pin_type(PORT, gpio->pin_no, gpio->optype);
	
	/*To configure the pin pull-up or pull-down function*/
	// gpio_configure_pin_pull(PORT, gpio->pin_no, gpio->pulltype);
	
	/*To configure the alternate function for the pin*/
	gpio_configure_alternate_function(PORT, gpio->pin_no, gpio->alternate_enable, gpio->alternate_function);
}
	
static void gpio_configure_digital_enable(GPIOA_Type *PORT, uint32_t pin_no, uint32_t digital_enable){
	/* Enable the digital Functionality for the pin*/
	if(digital_enable){
		PORT->DEN |= (1 << pin_no);
	}
	else{
		PORT->DEN &= (~(1 << pin_no));
	}
}

static void gpio_configure_pin_type(GPIOA_Type *PORT,uint32_t pin_no, uint32_t optype){
	/* Enable the output type for the pin*/
	if(optype){
		PORT->DIR |= (optype << pin_no);
	}
	else{
		PORT->DIR &= ~(optype << pin_no);
	}
}

static void gpio_configure_pin_pull(GPIOA_Type* PORT, uint32_t pin_no, uint32_t pulltype){
	PORT->PUR &= ~(1 << pin_no);
	PORT->PUR |= (pulltype << pin_no);
}

static void gpio_configure_alternate_function(GPIOA_Type *port, uint32_t pin_no, uint32_t alternate_enable, uint32_t alternate_function){
	if(alternate_enable){
		port->AFSEL |= (1 << pin_no);
		port->PCTL &= (~(0x0ful << (pin_no*4)));
		port->PCTL |= (alternate_function << (pin_no*4));
	}
}



