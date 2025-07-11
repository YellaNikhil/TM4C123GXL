#include "serial.h"

static void serial_print_char(char ch);
static uint8_t serial_flag_check_status(uint32_t status_name);
static char serial_read_char(void);

static char buffer_data[DATA_SIZE];

void serial_begin(void) //UART0 -> PA0(RX) PA1(TX) 9600
{
	SYSCTL->RCGCUART |= (1<<0); //enable the uart0 clock
	SYSCTL->RCGCGPIO |= (1<<0); //enable the GPIOA clock
	
	GPIOA->AFSEL |= (1<<0)|(1<<1); //set alternative function of PA[0, 1] as uart0 pins
	GPIOA->PCTL |= (1<<0)|(1<<4);  //set uart mode
	GPIOA->DEN |= (1<<0)|(1<<1); //digitize the GPIO pins of uart0
	
	UART0->CTL &= ((unsigned)(~(1<<0))) & ((unsigned)(~(1<<8))) & ((unsigned)(~(1<<9))); //disable uart0, TX and RX
	UART0->IBRD = 104;  //set baud rate integer value in IBRD 
	UART0->FBRD = 11; 	//set baud rate decimal value in FBRD 
	UART0->LCRH |= (3<<5); //set data length in the transmission
	UART0->CC = 0x05; //select clock source
	UART0->CTL |= (1<<0)|(1<<8)|(1<<9); //enable uart0, TX and RX
}


//static void uart_send_data(uint16_t Data)
//{
//  /* Transmit Data */
//  UART0->DR = (Data & (uint16_t)0x00FF);
//}

// rewrite function for using printf function
//int fputc(int ch, FILE *f)
//{	
//	while((UART0->FR	& (1<<5))!=0){}		
//	serial_print_char(ch);
//	return (ch);
//}

/**
	* @brief Funtion used to print the string to the console
	* @param string 
	* @retval none
	*/
void serial_print(char *str){
	/*Iterating over the string to print it to console */
	while(*str){
		serial_print_char(*(str++));
	}
}


/**
	* @brief API used to select the data size of the device
	* @param string
	* @retval none
	*/
void serial_println(char *str){
	/*Iterating over the string to print it to console */
	serial_print(str);
	serial_print_char('\n');
}

/**
	* @brief API used to select the data size of the device
	* @param SPI Typedef Structure
	* @retval none
	*/
char* serial_read(void){
	char incoming_byte;
	uint8_t buffer_index = 0;
	do{
		incoming_byte = serial_read_char();
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
	}while(buffer_index < DATA_SIZE - 1);
	buffer_data[DATA_SIZE-1] = '\0';
	return buffer_data;
}



/**
	* @brief API used to select the data size of the device
	* @param SPI Typedef Structure
	* @param datasize 
	* @param LSB or MSB data
	* @retval none
	*/
static void serial_print_char(char ch){
	 /* Check if previous data is transmitted or not */
	//while((UART0->FR & UART_TX_FULL) != 0);
	while(serial_flag_check_status(UART_TX_FULL));
	 
	/* Put the character into the Data Register*/
	UART0->DR = ch;
}

static char serial_read_char(void){
	char ch;
	
	/* Checking if the data received is empty or not. if empty try to get the data.*/
	// while((UART0->FR & UART_RX_EMPTY) == 0); 
	//while(serial_flag_check_status(UART_RX_EMPTY) == 0);
	while((UART0->FR & (1<<4)) != 0); 
	
	/* We can also use RIS register to check but it will only check for end of transmission or receiving. */
	ch = (char)(UART0->DR & 0xff);
	
	/*Check if the RX FIFO is full*/
	// while((UART0->FR & UART_RX_FULL) == 0);
	// while(serial_flag_check_status(UART_RX_FULL));
	
	return ch;
}

static uint8_t serial_flag_check_status(uint32_t status_name){
	if(UART0->FR & status_name)
  {
    	return HIGH;
  }
  return LOW;
}
