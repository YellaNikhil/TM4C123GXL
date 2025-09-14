#include "servo_motor.h"
#include "gpio_registers.h"

#include<TM4C123GH6PM.h>

void init_servo_motor(void){
	SYSCTL->RCGCPWM |= (1<<1); //clock setting for pwm1 clock
	(SYSCTL->RCGCGPIO) |= (1<<5); //enable GPIOF clock
	
	GPIOF->AFSEL |= (1<<2); //select PF2 as alternative function pwm1
	GPIOF->PCTL |= (5<<8);  //set PF2 as pwm1 output
	GPIOF->DEN |= (1<<2);		//enable PF2 digital function
	

	USEPWMDIV();	
	SYSCTL->RCC &= (~(0x7UL << 17));
	SYSCTL->RCC |= (0x2ul << 17);
	
	PWM1->_3_CTL &= (unsigned)(~(1<<0)); // first disable pwm1 counter
	PWM1->_3_CTL &= (unsigned)(~(1<<1)); // select the downward counter
	PWM1->_3_LOAD = (40000); //set the pwm1 period 50Hz
	PWM1->_3_CMPA = SERVO_DEGREES_BASE; //set duty cycle 0%
	PWM1->_3_GENA |= (3<<2); //set pwm1 high or low voltage, when matches PWMCMPA
	PWM1->_3_GENA	|= (2<<6); //set PWM1 high or low voltage depending on the direction of counter
	PWM1->_3_CTL |= (1<<0); //enable pwm1 counter
	PWM1->ENABLE |=	(1<<6); //enable pwm1 channel
}
	
void run_servo_motor(void){
		turn_servo_degrees_0();
		delay_ms(1000);
		turn_servo_degrees_45();
		delay_ms(1000);
		turn_servo_degrees_90();
		delay_ms(1000);
		turn_servo_degrees_180();
		delay_ms(1000);
}

void turn_servo_degrees_0(void){
		PWM1->_3_CMPA = SERVO_DEGREES_0;
}

void turn_servo_degrees_45(void){
	PWM1->_3_CMPA = SERVO_DEGREES_45;
}

void turn_servo_degrees_90(void){
		PWM1->_3_CMPA = SERVO_DEGREES_90;
}

void turn_servo_degrees_180(void){
	PWM1->_3_CMPA = SERVO_DEGREES_180;
}

void turn_servo_degrees(uint32_t value){
	PWM1->_3_CMPA = SERVO_DEGREES_CHANGE(value);
}
