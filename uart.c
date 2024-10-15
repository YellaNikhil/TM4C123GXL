#include "uart.h"



static void uart_transmit_byte(UART0_Type*, const char);
static char uart_receive_data_byte(const UART0_Type* uart_handle);


static char uart_msg[100];

void uart_init(uart_handler* uart_handle){
	
	/* Initialize the uart port for rx pin */
	gpio_init(uart_handle->rx->port, uart_handle->rx);
	
	/* Initialize the uart port for tx pin */
	gpio_init(uart_handle->tx->port, uart_handle->tx);
	
	uart_handle->uart->CTL &= ((unsigned)(~(1<<0))) & ((unsigned)(~(1<<8))) & ((unsigned)(~(1<<9))); //disable uart0, TX and RX
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
		char ch = '\t';
		while(index < 99 && (ch != '\n' || ch!='\r' || ch!='\0' || ch!='0')){
			ch = uart_receive_data_byte(uart_handle->uart);
			uart_msg[index++] = ch;
		}
//		uart_msg[index + 1] = '\0';
		return uart_msg;
}

static char uart_receive_data_byte(const UART0_Type* uart_module){
	while((uart_module->FR & (1<<6)) ==  0); // Check if Data is still received state.
	char data = uart_module->DR;
	return (unsigned char)data;
}

static void uart_transmit_byte(UART0_Type* uart_module, const char ch){
	while((uart_module->FR & (1<<5)) != 0);
	uart_module->DR = ch;
}

