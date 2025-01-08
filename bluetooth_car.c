#include "bluetooth_car.h"

static uint8_t bluetooth_available(uart_handler* bluetooth);
static void bluetooth_write(uart_handler *bluetooth, const char* data);
static uint8_t bluetooth_read(uart_handler *bluetooth);
	
void bluetooth_car_init(uart_handler* bluetooth, car_handler* car){
	/*Bluetooth initialization */
	uart_init(bluetooth);
	
	/*Initialization of car */
	car_init(car);
}


void bluetooth_car_run(uart_handler* bluetooth, car_handler* car){
	char data = ' ', prev_data = ' ';
	uint8_t duty_cycle = 0;
	uint32_t speed = 0;
	
	char msg[100];
	
	/* 1. Check for data from bluetooth if any is available */
	while(bluetooth_available(bluetooth) != 0){
		/* 2. if data is available, read from it */
		data = (char)bluetooth_read(bluetooth);
		
		/*3. Send ACK to transmitter about the direction command is received */
		sprintf(msg, "Received data : %s\r\n", &data);
		bluetooth_write(bluetooth, msg);
		
		/* 4. Fetch the value of speed from the transmitter */
		duty_cycle = ((uint8_t)bluetooth_read(bluetooth) - '0')*10; // Receiving characters from '1' to '9' and using them as percentages
		speed = ((100 - duty_cycle)*4096)/100;
		
		#if 1
			sprintf(msg, "Received speed : %d\r\n",  duty_cycle);
			bluetooth_write(bluetooth, msg);
		#endif
		
		car->front_left_motor->speed = speed;
		car->front_right_motor->speed = speed;
		car->back_left_motor->speed = speed;
		car->back_right_motor->speed = speed;
	
		/* 4. Check if it is a valid data and not the same instruction as before */
		if(data != prev_data){
			/* 5. Based on the new data, give directions to car which way to move */
			switch(data){
				case 'F':
				case 'f':
					car_move_forward(car);
					break;
				case 'B':
				case 'b':
					car_move_backward(car);
					break;
				case 'R':
				case 'r':
					car_move_right(car);
					break;
				case 'L':
				case 'l':
					car_move_left(car);
					break;
				case 'S':
				case 's':
					stop_car(car);
					break;
				default:
					break;
			}
		}
	}
}


static uint8_t bluetooth_available(uart_handler* bluetooth){
	uint8_t available = bluetooth->uart->FR & (1 << 4);
	return available;
}


static uint8_t bluetooth_read(uart_handler* bluetooth){
    uint8_t data;
	  while(bluetooth_available(bluetooth) != 0){} /* wait until Rx buffer is not full */
    while((data = (uint8_t)bluetooth->uart->DR) & (data == '\r' || data == '\n')){
			
		}
    return data; 
}


static void bluetooth_write(uart_handler *bluetooth, const char* data){
	 uart_transmit_data(bluetooth, data);
}
