#include "l_298n_motor_driver.h"
#include "servo_motor.h"

static void motor_pwm_wave_enable(PWM0_Type *pwm_port, uint32_t pin_type);
static void set_speed_of_motor(PWM0_Type* pwm_port, uint32_t pwm_type, uint32_t speed);
	
void motor_init(motor_handler *motor){
	/*Initiallizing the gpio pins for the motor controlling */
	gpio_init(motor->high_pin->port, motor->high_pin);
	gpio_init(motor->low_pin->port, motor->low_pin);
	gpio_init(motor->pwm_pin->port, motor->pwm_pin);
	
	motor_pwm_wave_enable(motor->pwm, motor->pwm_type);
}

void move_forward(motor_handler *motor){
	
	/*Enabling the direction of motor in forward direction */
	set_high_port_pin(motor->high_pin->port, motor->high_pin->pin_no);
	set_low_port_pin(motor->low_pin->port, motor->low_pin->pin_no);
	
	/*Setting the speed of the motor*/
	set_speed_of_motor(motor->pwm, motor->pwm_type, motor->speed);
	
}

void move_backward(motor_handler *motor){
	
	/*Enabling the direction of motor in backward direction */
	set_low_port_pin(motor->high_pin->port, motor->high_pin->pin_no);
	set_high_port_pin(motor->low_pin->port, motor->low_pin->pin_no);
	
	
	/*Setting the speed of the motor*/
	set_speed_of_motor(motor->pwm, motor->pwm_type, motor->speed);
}

void stop_movement(motor_handler *motor){
	/*Enabling the direction of motor in backward direction */
	set_low_port_pin(motor->high_pin->port, motor->high_pin->pin_no);
	set_low_port_pin(motor->low_pin->port, motor->low_pin->pin_no);
	
	
	/*Setting the speed of the motor*/
	set_speed_of_motor(motor->pwm, motor->pwm_type, 0);
}

static void set_speed_of_motor(PWM0_Type* pwm_port, uint32_t pwm_type, uint32_t speed){
	/*Assuming speed is a 12bit range variable value from ADC */
	switch(pwm_type){
		case 0:
			pwm_port->_0_CMPA = speed;
			break;
		case 1:
			pwm_port->_0_CMPB = speed;
			break;
		case 2:
			pwm_port->_1_CMPA = speed;
			break;
		case 3:
			pwm_port->_1_CMPB = speed;
			break;
		case 4:
			pwm_port->_2_CMPA = speed;
			break;
		case 5:
			pwm_port->_2_CMPB = speed;
			break;
		case 6:
			pwm_port->_3_CMPA = speed;
			break;
		case 7:
			pwm_port->_3_CMPB = speed;
			break;
		default:
			break;
	}
}


static void motor_pwm_wave_enable(PWM0_Type *pwm_port, uint32_t pin_type){
		
	/* PWM frequency should be anywhere between 500Hz to 20KHz. Need to change the below values accordingly.*/ 
	#if 1
	/* There are four generators controlling two outputs for each PWM module
	  The PWM0 block produces the MnPWM0 and MnPWM1 outputs, the PWM1 block producestheMnPWM2
 and MnPWM3 outputs,the PWM2 block produces the MnPWM4 and MnPWM5 outputs, and the PWM3
 block produces the MnPWM6 and MnPWM7 outputs. - Read Datasheet Page 1266
	IMP: They share same LOAD and COUNTER registers , in short, same frequencies are generated for both of the output signals of a generator 
	For M0PWM0 and M0PWM1 has same frequencies but with different comparators, CMPA & CMPB, we can acheive different duty cycles.*/
	
	switch(pin_type){
		case 0:
			pwm_port->_0_CTL&= (unsigned)(~(1<<0)); // first disable pwm1 counter
			pwm_port->_0_CTL &= (unsigned)(~(1<<1)); // select the downward counter
			pwm_port->_0_LOAD = (4095); //set the pwm0 period 2MHz system clock to acheive 488.89Hz ~= 490Hz
			pwm_port->_0_CMPA = 4095; //set duty cycle 0%
			pwm_port->_0_GENA |= (3<<2); //set PWM0A high, when matches counter = Load Value
			pwm_port->_0_GENA	|= (2<<6); //set PWM0A low, when PWM0CMPA = counter value
			pwm_port->_0_CTL |= (1<<0); //enable pwm0 counter
			pwm_port->ENABLE |=	(1<<0); //enable MnPWM0 channel
			break;
		case 1:
			pwm_port->_0_CTL&= (unsigned)(~(1<<0)); // first disable pwm1 counter
			pwm_port->_0_CTL &= (unsigned)(~(1<<1)); // select the downward counter
			pwm_port->_0_LOAD = (4095); //set the pwm0 period 2MHz system clock to acheive 488.89Hz ~= 490Hz
			pwm_port->_0_CMPB = 4095; //set duty cycle 0%
			pwm_port->_0_GENB |= (3<<2); //set PWM0B high, when matches counter = Load Value
			pwm_port->_0_GENB	|= (2<<6); //set PWM0B low, when PWM0CMPB = counter value
			pwm_port->_0_CTL |= (1<<0); //enable PWM0 counter
			pwm_port->ENABLE |=	(1<<1); //enable MnPWM1 channel
			break;
		case 2:
			pwm_port->_1_CTL&= (unsigned)(~(1<<0)); // first disable pwm1 counter
			pwm_port->_1_CTL &= (unsigned)(~(1<<1)); // select the downward counter
			pwm_port->_1_LOAD = (4095); //set the pwm1 period 2MHz system clock to acheive 488.89Hz ~= 490Hz
			pwm_port->_1_CMPA = 4095; //set duty cycle 0%
			pwm_port->_1_GENA |= (3<<2); //set PWM1A high, when matches counter = Load Value
			pwm_port->_1_GENA	|= (2<<6); //set PWM1A low, when PWM1CMPA = counter value
			pwm_port->_1_CTL |= (1<<0); //enable PWM1 counter
			pwm_port->ENABLE |=	(1<<2); //enable MnPWM2 channel
			break;
		case 3:
			pwm_port->_1_CTL&= (unsigned)(~(1<<0)); // first disable pwm1 counter
			pwm_port->_1_CTL &= (unsigned)(~(1<<1)); // select the downward counter
			pwm_port->_1_LOAD = (4095); //set the pwm1 period 2MHz system clock to acheive 488.89Hz ~= 490Hz
			pwm_port->_1_CMPB = 4095; //set duty cycle 0%
			pwm_port->_1_GENB |= (3<<2); //set PWM1B high, when matches counter = Load Value
			pwm_port->_1_GENB	|= (2<<6); //set PWM1B low, when PWM1CMPB = counter value
			pwm_port->_1_CTL |= (1<<0); //enable PWM1 counter
			pwm_port->ENABLE |=	(1<<3); //enable MnPWM3 channel
			break;
		case 4:
			pwm_port->_2_CTL &= (unsigned)(~(1<<0)); // first disable pwm1 counter
			pwm_port->_2_CTL &= (unsigned)(~(1<<1)); // select the downward counter
			pwm_port->_2_LOAD = (4095); //set the PWM2 period 2MHz system clock to acheive 488.89Hz ~= 490Hz
			pwm_port->_2_CMPA = 4095; //set duty cycle 0%
			pwm_port->_2_GENA |= (3<<2); //set PWM2A high, when matches counter = Load Value
			pwm_port->_2_GENA	|= (2<<6); //set PWM2A low, when PWM2CMPA = counter value
			pwm_port->_2_CTL |= (1<<0); //enable PWM2 counter
			pwm_port->ENABLE |=	(1<<4); //enable MnPWM4 channel
			break;
		case 5:
			pwm_port->_2_CTL &= (unsigned)(~(1<<0)); // first disable pwm1 counter
			pwm_port->_2_CTL &= (unsigned)(~(1<<1)); // select the downward counter
			pwm_port->_2_LOAD = (4095); //set the pwm2 period 2MHz system clock to acheive 488.89Hz ~= 490Hz
			pwm_port->_2_CMPB = 4095; //set duty cycle 0%
			pwm_port->_2_GENB |= (3<<2); //set PWM2B high, when matches counter = Load Value
			pwm_port->_2_GENB	|= (2<<6); //set PWM2B low, when PWM2CMPB = counter value
			pwm_port->_2_CTL |= (1<<0); //enable PWM2 counter
			pwm_port->ENABLE |=	(1<<5); //enable MnPWM5 channel
			break;
		case 6:
			pwm_port->_3_CTL&= (unsigned)(~(1<<0)); // first disable pwm1 counter
			pwm_port->_3_CTL &= (unsigned)(~(1<<1)); // select the downward counter
			pwm_port->_3_LOAD = (4095); //set the pwm3 period 2MHz system clock to acheive 488.89Hz ~= 490Hz
			pwm_port->_3_CMPA = 4095; //set duty cycle 0%
			pwm_port->_3_GENA |= (3<<2); //set PWM3A high, when matches counter = Load Value
			pwm_port->_3_GENA	|= (2<<6); //set PWM3A low, when PWM3CMPA = counter value
			pwm_port->_3_CTL |= (1<<0); //enable pwm3 counter
			pwm_port->ENABLE |=	(1<<6); //enable MnPWM6 channel
			break;
		case 7:
			pwm_port->_3_CTL&= (unsigned)(~(1<<0)); // first disable pwm1 counter
			pwm_port->_3_CTL &= (unsigned)(~(1<<1)); // select the downward counter
			pwm_port->_3_LOAD = (4095); //set the pwm3 period 2MHz system clock to acheive 488.89Hz ~= 490Hz
			pwm_port->_3_CMPB = 4095; //set duty cycle 0%
			pwm_port->_3_GENB |= (3<<2); //set PWM3B high, when matches counter = Load Value
			pwm_port->_3_GENB	|= (2<<6); //set PWM3B low, when PWM3CMPB = counter value
			pwm_port->_3_CTL |= (1<<0); //enable PWM3 counter
			pwm_port->ENABLE |=	(1<<7); //enable MnPWM7 channel
			break;
		default:
			break;
	}
	#endif
}
