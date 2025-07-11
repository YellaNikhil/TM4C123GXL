#include "uart.h"



static void uart_transmit_byte(UART0_Type*, const char);


static char uart_msg[101];

void uart_init(uart_handler* uart_handle){
	
	/* Initialize the uart port for rx pin */
	gpio_init(uart_handle->rx->port, uart_handle->rx);
	
	/* Initialize the uart port for tx pin */
	gpio_init(uart_handle->tx->port, uart_handle->tx);
	
	uart_handle->uart->CTL = 0;//&= ((unsigned)(~(1<<0))) & ((unsigned)(~(1<<8))) & ((unsigned)(~(1<<9))); //disable uart0, TX and RX
	uart_handle->uart->IBRD = uart_handle->baud_rate_integer_value;  //set baud rate integer value in IBRD 
	uart_handle->uart->FBRD = uart_handle->baud_rate_decimal_value; 	//set baud rate decimal value in FBRD 
	uart_handle->uart->LCRH |= uart_handle->data_length; //set data length in the transmission
	uart_handle->uart->CC = uart_handle->clock_source; //select clock source
	uart_handle->uart->CTL |= (1<<0)|(1<<8)|(1<<9); //enable uart0, TX and RX
}

void uart_transmit_data(uart_handler *uart_handle, const char *data){
	while(*data){
		uart_transmit_byte(uart_handle->uart, *(data++));
	}
}

char *uart_receive_data(uart_handler *uart_handle){
	int index = 0;
	char incoming_byte;
	do
	{
		incoming_byte = uart_receive_data_byte(uart_handle->uart);
		if (incoming_byte == '\n'){// Command ends with \n
			uart_msg[index] = '\0'; // Null-terminate the string
			break;
		}
		else if (incoming_byte != '\r'){ // Ignore \r
			uart_msg[index++] = incoming_byte;
		}
	}while (index <= 100 && (incoming_byte != '\0' || incoming_byte != NULL));
	uart_msg[index] = '\0';
	return uart_msg;
}

char uart_receive_data_byte(const UART0_Type *uart_base)
{
	char data;
	while ((uart_base->FR & (1 << 4)) != 0); /*Checking if the DR register is empty else break loop */		 
	data = (uint8_t)(uart_base->DR);
	return data;
}

static void uart_transmit_byte(UART0_Type *uart_module, const char ch)
{
	while ((uart_module->FR & UART_TX_FIFO_FULL) != 0); /* Checking if the DR register is full else break loop */
	uart_module->DR = ch;
}
