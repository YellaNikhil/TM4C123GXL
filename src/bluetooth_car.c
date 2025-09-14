#include "bluetooth_car.h"


uint8_t buffer_index = 0;
char buffer_data[3];

static uint8_t bluetooth_available(uart_handler* bluetooth);
static void bluetooth_write(uart_handler *bluetooth, const char* data);
static void bluetooth_read(uart_handler *bluetooth);
	
	
void bluetooth_car_init(uart_handler* bluetooth, car_handler* car){
	/*Bluetooth initialization */
	uart_init(bluetooth);
	
	/*Initialization of car */
	car_init(car);
}


void bluetooth_car_run(uart_handler* bluetooth, car_handler* car){
	uint8_t data = ' ', prev_data = ' ';
	uint8_t duty_cycle = 0;
	uint32_t speed = 50;
	
	char msg[100];
	
	/* 1. Check for data from bluetooth if any is available */
	//while(1){
		/* 2. if data is available, read from it */
		bluetooth_read(bluetooth);
		
		data = buffer_data[0];
		//bluetooth_write(bluetooth, "Enter Direction : \r\n");
		//data = uart_receive_data_byte(bluetooth->uart);
	
		/*3. Send ACK to transmitter about the direction command is received */
		sprintf(msg, "Received direction : %c\r\n", data);
		//sprintf(msg, "Received Data : %s", buffer_data);
		bluetooth_write(bluetooth, msg);
		
		#if 1
		/* 4. Fetch the value of speed from the transmitter */
		//duty_cycle = ((uint8_t)bluetooth_read(bluetooth) - '0')*10; // Receiving characters from '1' to '9' and using them as percentages
		duty_cycle = buffer_data[1];
		//bluetooth_write(bluetooth, "Enter speed : \r\n");
		//sprintf(msg, "Enter speed : %d\r\n", duty_cycle);
		//duty_cycle = (uint8_t)uart_receive_data_byte(bluetooth->uart) - '0';
		speed = ((100 - duty_cycle)*4096)/100;
		
		
		sprintf(msg, "Received speed : %c\r\n", duty_cycle);
		bluetooth_write(bluetooth, msg);
	
	
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
		#endif
	//}
}


static uint8_t bluetooth_available(uart_handler* bluetooth){
	uint8_t available = bluetooth->uart->FR & (1 << 4);
	return available;
}

#if 0
static void bluetooth_read(uart_handler* bluetooth){
    uint8_t incoming_byte;
	  while(bluetooth_available(bluetooth) != 0){} /* wait until Rx buffer is not full */
		buffer_index = 0;
    while(bluetooth_available(bluetooth)){
			incoming_byte = (uint8_t)bluetooth->uart->DR;
			if (incoming_byte == '\n') {  // Command ends with \n
            buffer_data[buffer_index] = '\0';  // Null-terminate the string
            // process_command(uart_buffer);  // Process the command
            buffer_index = 0;  // Reset the buffer index
        } else if (incoming_byte != '\r') {  // Ignore \r
            buffer_data[buffer_index++] = incoming_byte;
            if (buffer_index >= BUFFER_SIZE - 1) {
                buffer_data[BUFFER_SIZE - 1] = '\0';  // Null-terminate to prevent overflow
                buffer_index = 0;  // Reset if overflow occurs
            }
        }
		}
}
#endif

static void bluetooth_read(uart_handler *bluetooth){ /* We are expecting only two characters to get from Bluetooth Data */
	char incoming_byte;
	buffer_index = 0;
	do{
		incoming_byte = uart_receive_data_byte(bluetooth->uart);
		if (incoming_byte == '\n') {  // Command ends with \n
            buffer_data[buffer_index] = '\0';  // Null-terminate the string
            //process_command(uart_buffer);  // Process the command
            //buffer_index = 0;  // Reset the buffer index
    } 
		else if (incoming_byte != '\r' && incoming_byte != NULL) {  // Ignore \r
            buffer_data[buffer_index++] = incoming_byte;
            #if 0
						if (buffer_index >= BUFFER_SIZE - 1) {
                buffer_data[BUFFER_SIZE - 1] = '\0';  // Null-terminate to prevent overflow
                buffer_index = 0;  // Reset if overflow occurs
            }
					 #endif
    }
	}while(buffer_index < BUFFER_SIZE - 1);
	buffer_data[BUFFER_SIZE-1] = '\0';
}

//static void bluetooth_read(uart_handler* bluetooth) {
//    char incoming_byte;

//		while(bluetooth_available(bluetooth));
//    while (bluetooth_available(bluetooth) == 0) {  // Function to check if data is available
//        incoming_byte = (uint8_t)bluetooth->uart->DR;  // Read a byte from UART

//        if (incoming_byte == '\n') {  // Command ends with \n
//            buffer_data[buffer_index] = '\0';  // Null-terminate the string
//            process_command(uart_buffer);  // Process the command
//            buffer_index = 0;  // Reset the buffer index
//        } else if (incoming_byte != '\r') {  // Ignore \r
//            uart_buffer[buffer_index++] = incoming_byte;
//            if (buffer_index >= BUFFER_SIZE - 1) {
//                uart_buffer[BUFFER_SIZE - 1] = '\0';  // Null-terminate to prevent overflow
//                buffer_index = 0;  // Reset if overflow occurs
//            }
//        }
//    }
//}

static void bluetooth_write(uart_handler *bluetooth, const char* data){
	 uart_transmit_data(bluetooth, data);
}
