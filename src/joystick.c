#include "joystick.h"

static volatile uint32_t x_value = 0;

void init_joystick_ports(void){
	/*Enable clock for the GPIO port E and ADC0 */
	SYSCTL->RCGCGPIO |= 0x30;
  SYSCTL->RCGCADC |= 0x01;
	
	/* Digital Disable the PE3 */
	GPIOE->DEN &= (~(1U << 3));
	GPIOE->DIR |= (~(1U << 3));
	
	/*Analog Functionality of the PE3 is set to high */
	GPIOE->AFSEL |= 0x08;
	GPIOE->AMSEL |= 0x08;
	
	/* Enable the Analog ADC Registers*/
	ADC0->ACTSS &= (~(1U << 3)); /*Disabling SS3 */
	ADC0->EMUX  &= ~((uint32_t)(0xF000));
	ADC0->TSSEL |= 0x10; /*Enable PWM0 for SS3*/
	
	ADC0->SSMUX3 &= 0xFE; /* Set SS3 high for ADC0*/
	ADC0->SSCTL3 |= 0x06; /* Set END0 of the MUX0 in SS3 */
	
	ADC0->ACTSS |= 0x08; /*Enabling the SS3 */
	
	ADC0->SSOP3 |= 0x00; /*Set to low for using FIFO3 for storage of values */
	
//	GPIOF->DEN |= 0x0E;
//	GPIOF->DIR |= 0x0E;
//	GPIOF->DATA = 0x00;
}


uint32_t read_joystick(void){
	ADC0->PSSI |= (1 << 3);
	while((ADC0->RIS & 0x08) == 0x00);
	x_value = ADC0->SSFIFO3&0xFFF;
	ADC0->ISC |= (1 <<3);
	return x_value;
}

void run_joystick(void){
	read_joystick();
}


