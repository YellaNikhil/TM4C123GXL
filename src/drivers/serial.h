#ifndef _SERIAL_H_
#define _SERIAL_H_

#include "gpio_registers.h"
#include "uart.h"


#define UART_TX_EMPTY 0x80
#define UART_RX_FULL 0x40
#define UART_TX_FULL 0x20
#define UART_RX_EMPTY 0x10

#define DATA_SIZE 100

/*Initialize the Serial output functionality */
void serial_begin(void);

/*Print the string to the console */
void serial_print(char *);

/*Print the string to the console with an new line at the end. */
void serial_println(char *);

/*Reads the input from the console */
char* serial_read(void);

#endif
