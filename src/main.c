#include "gpio_registers.h"
#include "serial.h"
#include "lcd_raw.h"
#include "uart.h"
#include "bluetooth_car.h"

//#define PRESCALER_VALUE 15


/******************************************************************************************************************/
/*-------------------------------------------Global Variables ----------------------------------------------------*/
/******************************************************************************************************************/
static char msg[100];

/* bluetooth handler and gpio pins of tx, rx to connect to bluetooth device */
static uart_handler bluetooth;
static gpio_info rx_pin, tx_pin;

/* Front Tires high pin - PA6, low pin - PA5 */
static gpio_info front_tires_high_pin, front_tires_low_pin;


/* Back Tires high pin - PE5, low pin - PE4 */
static gpio_info back_tires_high_pin, back_tires_low_pin;

/* Speed pins for all the four motors 
 * Front left motor  - PB4
 * Front right motor - PB5
 * Back left motor   - PB6 
 * Back right motor  - PB7
*/
static gpio_info back_right_speed_pin, back_left_speed_pin;
static gpio_info front_right_speed_pin, front_left_speed_pin;

/* Car hanlder variable to store the motors information, speed and direction */
static car_handler car;
static motor_handler front_left_motor, front_right_motor, back_left_motor, back_right_motor;


/******************************************************************************************************************/
/*------------------------------------------User Defined static Functions ----------------------------------------*/
/******************************************************************************************************************/
// static char read_uart_info(uart_handler* bluetooth);



/******************************************************************************************************************/
/*---------------------------------------------User Defined Functions --------------------------------------------*/
/******************************************************************************************************************/
void setup(void);
void loop(void);



//char UART0_Receiver(void)  
//{
//    char data;
//	  while((UART0->FR & (1<<4)) != 0); /* wait until Rx buffer is not full */
//    data = UART0->DR ;  	/* before giving it another byte */
//    return (unsigned char) data; 
//}


// static lcd_info lcd;

int main(void)
{	
	// init_sys_tick_timer();
	//LCD_init();
	//LCD_backlight();
	//LCD_set_cursor(0,1);
	//LCD_blink();
	//LCD_cursor();
	//char str[6] = {'H', 'e', 'l', 'l', 'o', '\0'};
	
	//	lcd.databits[0].digital_enable = 1;
	//	lcd.databits[0].optype = OUTPUT;
		
	// lcd_init(&lcd);
//  LCD_print("Hello, World!");
	// serial_begin();
	setup();
	while(1)
	{
		loop();
	}
}




void setup(void){
		
	SYSCTL->RCGCGPIO |= 0x17ul;
	SYSCTL->RCGCUART |= 0x08ul;
	SYSCTL->RCC |= (0x01ul << 20);
	SYSCTL->RCGCPWM |= 0x01ul;
	
	/* Clearing the PWMDIV in RCC register */
	SYSCTL->RCC &= (~(0x7UL << 17));
	
	/* Need to give a static value for different drives like L298N, and for TB6612FNB driver. */
	SYSCTL->RCC |= (0x2ul << 17);
	
	while (!(SYSCTL->RCGCPWM & (1 << 0)));
	init_sys_tick_timer();
	delay_us(DELAY_US_1000);
	
	/*Bluetooth variable assignment */
	tx_pin.port = GPIOC;
	tx_pin.digital_enable = HIGH;
	tx_pin.pin_no = PIN7;
	tx_pin.optype = OUTPUT;
	tx_pin.alternate_enable = HIGH;
	tx_pin.alternate_function = ALT_FUNC_UART_MODE;

	rx_pin.port = GPIOC;
	rx_pin.pin_no = PIN6;
	rx_pin.digital_enable = HIGH;
	rx_pin.optype = INPUT;
	rx_pin.alternate_enable = HIGH;
	rx_pin.alternate_function = ALT_FUNC_UART_MODE;

	bluetooth.uart = UART3;
	bluetooth.rx = &rx_pin;
	bluetooth.tx = &tx_pin;
	bluetooth.clock_source = 0; /* System Clock */
	bluetooth.baud_rate_decimal_value = UART_9600_DECIMAL;
	bluetooth.baud_rate_integer_value = UART_9600_INTERGER;
	bluetooth.interrupt_enable = LOW;
	bluetooth.data_length = (3<<5);
	
	
	/* Motor pins assignment */
	front_tires_high_pin.port = GPIOA;
	front_tires_high_pin.pin_no = PIN6;
	front_tires_high_pin.digital_enable = HIGH;
	front_tires_high_pin.optype = OUTPUT;
	front_tires_high_pin.alternate_enable = LOW;
	
	front_tires_low_pin.port = GPIOA;
	front_tires_low_pin.pin_no = PIN5;
	front_tires_low_pin.digital_enable = HIGH;
	front_tires_low_pin.optype = OUTPUT;
	front_tires_low_pin.alternate_enable = LOW;
	
	back_tires_high_pin.port = GPIOE;
	back_tires_high_pin.pin_no = PIN4;
	back_tires_high_pin.digital_enable = HIGH;
	back_tires_high_pin.optype = OUTPUT;
	back_tires_high_pin.alternate_enable = LOW;
	
	back_tires_low_pin.port = GPIOE;
	back_tires_low_pin.pin_no = PIN5;
	back_tires_low_pin.digital_enable = HIGH;
	back_tires_low_pin.optype = OUTPUT;
	back_tires_low_pin.alternate_enable = LOW;
	
	
	/* Motors speed controlling pins initialization */
  front_left_speed_pin.port = GPIOB;
	front_left_speed_pin.pin_no = PIN4;
	front_left_speed_pin.digital_enable = HIGH;
	front_left_speed_pin.optype = OUTPUT;
	front_left_speed_pin.alternate_enable = HIGH;
	front_left_speed_pin.alternate_function = ALT_FUNC_PWM0_MODE;
	
	front_right_speed_pin.port = GPIOB;
	front_right_speed_pin.pin_no = PIN5;
	front_right_speed_pin.digital_enable = HIGH;
	front_right_speed_pin.optype = OUTPUT;
	front_right_speed_pin.alternate_enable = HIGH;
	front_right_speed_pin.alternate_function = ALT_FUNC_PWM0_MODE;
	
	back_left_speed_pin.port = GPIOB;
	back_left_speed_pin.pin_no = PIN6;
	back_left_speed_pin.digital_enable = HIGH;
	back_left_speed_pin.optype = OUTPUT;
	back_left_speed_pin.alternate_enable = HIGH;
	back_left_speed_pin.alternate_function = ALT_FUNC_PWM0_MODE;
	
	back_right_speed_pin.port = GPIOB;
	back_right_speed_pin.pin_no = PIN7;
	back_right_speed_pin.digital_enable = HIGH;
	back_right_speed_pin.optype = OUTPUT;
	back_right_speed_pin.alternate_enable = HIGH;
	back_right_speed_pin.alternate_function = ALT_FUNC_PWM0_MODE;
	
	
	/*Assigning the pins to all 4 motors */
	front_left_motor.high_pin = &front_tires_high_pin;
	front_left_motor.low_pin = &front_tires_low_pin;
	front_left_motor.pwm_pin = &front_left_speed_pin;
	front_left_motor.pwm_type = 2;
	front_left_motor.pwm = PWM0;
	front_left_motor.speed = 0;
	
	front_right_motor.high_pin = &front_tires_high_pin;
	front_right_motor.low_pin = &front_tires_low_pin;
	front_right_motor.pwm_pin = &front_right_speed_pin;
	front_right_motor.pwm_type = 3;
	front_right_motor.pwm = PWM0;
	front_right_motor.speed = 0;
	
	back_left_motor.high_pin = &back_tires_high_pin;
	back_left_motor.low_pin = &back_tires_low_pin;
	back_left_motor.pwm_pin = &back_left_speed_pin;
	back_left_motor.pwm_type = 0;
	back_left_motor.pwm = PWM0;
	back_left_motor.speed = 0;
	
	back_right_motor.high_pin = &back_tires_high_pin;
	back_right_motor.low_pin = &back_tires_low_pin;
	back_right_motor.pwm_pin = &back_right_speed_pin;
	back_right_motor.pwm_type = 1;
	back_right_motor.pwm = PWM0;
	back_right_motor.speed = 0;
	
	/* Assigning all the motors to the car handle */
	car.front_left_motor = &front_left_motor;
	car.back_left_motor = &back_left_motor;
	car.front_right_motor = &front_right_motor;
	car.back_right_motor = &back_right_motor;
	
	
	serial_begin();
	
	/*Bluetooth Initialization */
	bluetooth_car_init(&bluetooth, &car);
}

void loop(void){
//	char data = read_uart_info(&bluetooth);
//	sprintf(msg, "The value is %s\r", &data);
//	serial_println("HelloWorld\r\n");
//	delay_ms(1000);
//  char *read_data = serial_read();
 serial_println("Hello World!\r\n");
 delay_ms(1000);
//	bluetooth_car_run(&bluetooth, &car);
}

//static char read_uart_info(uart_handler* uart_handle){
//    char data;
//	  while((uart_handle->uart->FR & (1<<4)) != 0){} /* wait until Rx buffer is not full */
//    data = (char)uart_handle->uart->DR ;  	/* before giving it another byte */
//    return data; 
//}

//static void timer_init(void){
//	SYSCTL->RCGCTIMER |= 2;  /*enable clock Timer1 subtimer A in run mode */
//	TIMER1->CTL = 0; /* disable timer1 output */
//	TIMER1->CFG = 0x4; /*select 16-bit configuration option */
//	TIMER1->TAMR = 0x02; /*select periodic down counter mode of timer1 */
//	TIMER1->TAILR = 0; /* TimerA counter starting count down value  */
//	TIMER1->TAPR = 16 - 1; // Setting a pre-scaler value
//	TIMER1->ICR = 0x1;          /* TimerA timeout flag bit clears*/
//	TIMER1->CTL |= 0x03;        /* enable Timer A after initialization */
//}

//static void delay_micro_seconds(uint32_t delay){
//		TIMER1->TAILR = delay - 4;  
//		TIMER1->ICR = 0x1;
//		while((TIMER1->RIS & 0x1) == 0);
//}


//static void receive_data(void){
//	while(read_port_pin(rx_pin.port, rx_pin.pin_no) != 0);
//	delay_micro_seconds(50);
//	uint32_t index = 0;
//	while(index < 8){
//		uint8_t state = read_port_pin(rx_pin.port, rx_pin.pin_no);
//		data |= (state << index);
//		index++;
//		delay_micro_seconds(80);
//	}
//}



