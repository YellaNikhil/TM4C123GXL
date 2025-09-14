#ifndef GPIO_REGISTERS_H
#define GPIO_REGISTERS_H

#include<stdint.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<TM4C123GH6PM.h>

//#define DELAY_1MS 62500UL
//#define DELAY_10MS 625000UL
#define DELAY_US_500 2075
#define DELAY_US_1000 4162
#define DELAY_MS_1000 1000


/* System Clock Enable */
#define RCGC_GPIO (*((__IO uint32_t *)0x400FE608))
#define GPIOA_CLK_ENABLE() ((RCGC_GPIO |= (1 << 0)))
#define GPIOB_CLK_ENABLE() ((RCGC_GPIO |= (1 << 1)))
#define GPIOC_CLK_ENABLE() ((RCGC_GPIO |= (1 << 2)))
#define GPIOD_CLK_ENABLE() ((RCGC_GPIO |= (1 << 3)))
#define GPIOE_CLK_ENABLE() ((RCGC_GPIO |= (1 << 4)))
#define GPIOF_CLK_ENABLE() ((RCGC_GPIO |= (1 << 5)))

#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7

#define LOW 0
#define HIGH 1
#define SET HIGH
#define UNSET LOW
#define INPUT LOW
#define OUTPUT HIGH

/* Alternate Function Declarations*/
#define ALT_FUNC_ANALOG_MODE 0x00
#define ALT_FUNC_UART_MODE 0x01
#define ALT_FUNC_SSI_MODE 0x02
#define ALT_FUNC_I2C_MODE 0x03
#define ALT_FUNC_PWM0_MODE 0x04
#define ALT_FUNC_PWM1_MODE 0x05
#define ALT_FUNC_PH_MODE 0x06
#define ALT_FUNC_TIMER_MODE 0x07
#define ALT_FUNC_CAN_MODE 0x08
#define ALT_FUNC_ANALOG_COMPARATOR_MODE 0x09
#define ALT_FUNC_TRACE_DATA_MODE 0x14


/* GPIO Lock Reset */
#define GPIOUNLOCK 0x4C4F434BUL


/* GPIO Port A Registers */
#define GPIODATA_PORT_A (*((volatile uint32_t*) 0X40004090))
#define GPIODEN_PORT_A (*((volatile uint32_t*) 0x4000451C))
#define GPIODIR_PORT_A (*((volatile uint32_t*) 0x40004400))
#define GPIOAFSEL_PORT_A (*((volatile uint32_t*) 0x40004420))
#define GPIOPUR_PORT_A (*((volatile uint32_t*) 0x40004510))
#define GPIOPDR_PORT_A (*((volatile uint32_t*) 0x40004514))
#define GPIOAMSEL_PORT_A (*((volatile uint32_t*) 0x40004528))
#define GPIOPCTL_PORT_A (*((volatile uint32_t*) 0x4000452C))
#define GPIOLOCK_PORT_A (*((volatile uint32_t*) 0x40004520))
#define GPIOCR_PORT_A (*((volatile uint32_t*) 0x40004524))
	

/*GPIO Port B Registers */
#define GPIODATA_PORT_B (*((volatile uint32_t*) 0X40005090))
#define GPIODEN_PORT_B (*((volatile uint32_t*) 0x4000551C))
#define GPIODIR_PORT_B (*((volatile uint32_t*) 0x40005400))
#define GPIOAFSEL_PORT_B (*((volatile uint32_t*) 0x40005420))
#define GPIOPUR_PORT_B (*((volatile uint32_t*) 0x40005510))
#define GPIOPDR_PORT_B (*((volatile uint32_t*) 0x40005514))
#define GPIOAMSEL_PORT_B (*((volatile uint32_t*) 0x40005528))
#define GPIOPCTL_PORT_B (*((volatile uint32_t*) 0x4000552C))
#define GPIOLOCK_PORT_B (*((volatile uint32_t*) 0x40005520))
#define GPIOCR_PORT_B (*((volatile uint32_t*) 0x40005524))



/* GPIO Port C Registers */
#define GPIODATA_PORT_C (*((volatile uint32_t*) 0x400063C0))
#define GPIODEN_PORT_C (*((volatile uint32_t*) 0x4000651C))
#define GPIODIR_PORT_C (*((volatile uint32_t*) 0x40006400))
#define GPIOAFSEL_PORT_C (*((volatile uint32_t*) 0x40006420))
#define GPIOPUR_PORT_C (*((volatile uint32_t*) 0x40006510))
#define GPIOPDR_PORT_C (*((volatile uint32_t*) 0x40006514))
#define GPIOAMSEL_PORT_C (*((volatile uint32_t*) 0x40006528))
#define GPIOPCTL_PORT_C (*((volatile uint32_t*) 0x4000652C))
#define GPIOLOCK_PORT_C (*((volatile uint32_t*) 0x40006520))
#define GPIOCR_PORT_C (*((volatile uint32_t*) 0x40006524))


/* GPIO Port D Registers */
#define GPIODATA_PORT_D (*((volatile uint32_t*) 0X40007300))
#define GPIODEN_PORT_D (*((volatile uint32_t*) 0x4000751C))
#define GPIODIR_PORT_D (*((volatile uint32_t*) 0x40007400))
#define GPIOAFSEL_PORT_D (*((volatile uint32_t*) 0x40007420))
#define GPIOPUR_PORT_D (*((volatile uint32_t*) 0x40007510)
#define GPIOPDR_PORT_D (*((volatile uint32_t*) 0x40007514))
#define GPIOLOCK_PORT_D (*((volatile uint32_t*) 0x40007520))
#define GPIOAMSEL_PORT_D (*((volatile uint32_t*) 0x40007528))
#define GPIOPCTL_PORT_D (*((volatile uint32_t*) 0x4000752C))
#define GPIOCR_PORT_D (*((volatile uint32_t*) 0x40007524))
	

/* GPIO Port E Registers */
#define GPIODATA_PORT_E (*((volatile uint32_t*) 0X400243FC))
#define GPIODIR_PORT_E (*((volatile uint32_t*) 0x40024400))
#define GPIODEN_PORT_E (*((volatile uint32_t*) 0x4002451C))
#define GPIOAFSEL_PORT_E (*((volatile uint32_t*) 0x40045420))
#define GPIOPUR_PORT_E (*((volatile uint32_t*) 0x40024510)
#define GPIOPDR_PORT_E (*((volatile uint32_t*) 0x40024514))
#define GPIOLOCK_PORT_E (*((volatile uint32_t*) 0x40024520))
#define GPIOAMSEL_PORT_E (*((volatile uint32_t*) 0x40024528))
#define GPIOPCTL_PORT_E (*((volatile uint32_t*) 0x4002452C))
#define GPIOCR_PORT_E (*((volatile uint32_t*) 0x40024524))


/* GPIO Port F Registers */
// #define GPIODATA_PORT_F (*((volatile uint32_t*) 0x4002507C))
#define GPIODATA_PORT_F (*((volatile uint32_t*) 0x400253FC))
#define GPIODEN_PORT_F (*((volatile uint32_t*) 0x4002551C))
#define GPIODIR_PORT_F (*((volatile uint32_t*) 0x40025400))
#define GPIOAFSEL_PORT_F (*((volatile uint32_t*) 0x40025420))
#define GPIOPUR_PORT_F (*((volatile uint32_t*) 0x40025510))
#define GPIOPDR_PORT_F (*((volatile uint32_t*) 0x40025514)
#define GPIOAMSEL_PORT_F (*((volatile uint32_t*) 0x40025528))
#define GPIOLOCK_PORT_F (*((volatile uint32_t*) 0x40025520))
#define GPIOPCTL_PORT_F (*((volatile uint32_t*) 0x4002552C))
#define GPIOCR_PORT_F (*((volatile uint32_t*) 0x40025524))

/* SysTick Clock Timers */
#define SYSTICK_STCTRL (*((volatile uint32_t*) 0xE000E010))
#define SYSTICK_STRELOAD (*((volatile uint32_t*) 0xE000E014))
#define SYSTICK_STCURRENT (*((volatile uint32_t*) 0xE000E018))


/*Data Structure to store gpio info*/
typedef struct{
	/*Port of the GPIO pin */
	GPIOA_Type *port;
	
	/*Pin no of the GPIO PORT*/
	uint32_t pin_no;
	
	/* Enable or Disable the digital for pin*/
	uint32_t digital_enable;
	
	/*GPIO PORT operation type input(0) or output(1) */
	uint32_t optype;
	
	/*GPIO Pin Pull up or pull down mode */
	uint32_t pulltype;
	
	/*Alternate Functionality enable of the GPIO pin*/
	uint32_t alternate_enable;
	
	/*Set alternate functionality for the GPIO pin*/
	uint32_t alternate_function;
}gpio_info;

/* GPIO Driver Functions */

void set_low_port_pin(GPIOA_Type* port, uint32_t pin_no);

void set_high_port_pin(GPIOA_Type* port, uint32_t pin_no);

void turn_on_port_pin(volatile uint32_t* PORT, uint32_t value);

void turn_off_port_pin(volatile uint32_t* PORT, uint32_t value);

uint8_t read_port_pin(volatile uint32_t* PORT, uint32_t pin_no);

void gpio_init(GPIOA_Type* PORT, gpio_info*);

void init_sys_tick_timer(void);

void delay(uint32_t);

void delay_ms(uint32_t);

void delay_us(uint32_t);  

void delay_wait_1s(void);
	
#endif
