#include <stdint.h>
#include <stdio.h>
#include <gpio_registers.h>
#include <uart.h>
#include <serial.h>
#include <queue.h>

void setup(void);
void loop(void);

// UART Helper Functions
char UART_Receiver(UART0_Type *uart);

uart_handler serial;

int main(void) {
    setup();
    while(1){
        loop();
    }
    return 0;
}

void setup(void) {
    // Initialize SYS Tick Timer
    // This function is typically used for timing operations, but here we just call it to ensure
    // the system timer is set up correctly.
    // Note: The actual implementation of init_sys_tick_timer() is not provided in the context
    // but it should be defined in your project to initialize the system tick timer.
    // Assuming init_sys_tick_timer() is defined in your project.
    // If not, you can remove this line or implement it as needed.
    init_sys_tick_timer();

    // Initialize GPIO Port F
    GPIOF_CLK_ENABLE();
    
    //Initialize UART Clock
    GPIOA_CLK_ENABLE();
    SYSCTL->RCGCUART |= (1 << 0); // Enable UART0 clock

    // UART Configuration
    gpio_info tx = {
        .port = GPIOA,
        .pin_no = PIN1, // Using PA0 for TX
        .digital_enable = 1,
        .optype = OUTPUT,
        .pulltype = 0, // No pull-up or pull-down
        .alternate_enable = 1,
        .alternate_function = ALT_FUNC_UART_MODE
    };

    gpio_info rx = {
        .port = GPIOA,
        .pin_no = PIN0, // Using PA1 for RX
        .digital_enable = 1,
        .optype = INPUT,
        .pulltype = 0, // No pull-up or pull-down
        .alternate_enable = 1,
        .alternate_function = ALT_FUNC_UART_MODE
    };    

    serial.uart = UART0;
    serial.tx = &tx;
    serial.rx = &rx;
    serial.baud_rate_integer_value = 104; // Example value for 9600 baud rate
    serial.baud_rate_decimal_value = 11;  // Example value for 9600 baud rate
    serial.clock_source = 0;              // Use system clock
    serial.data_length = 0x60;            // 8 data bits, no parity,
    serial.parity_bit = 0;                // No parity
    serial.interrupt_enable = 0;          // No interrupts
    serial.data = NULL;                    // No data buffer
    
    // Initialize GPIO for LED on PF1
    gpio_info led_info = {
        .port = GPIOF,
        .pin_no = PIN1, // Using PF1 for LED
        .digital_enable = 1,
        .optype = OUTPUT,
        .pulltype = 0, // No pull-up or pull-down
        .alternate_enable = 0,
        .alternate_function = 0 // No alternate function
    };
    

    // Initialize UART
    uart_init(&serial); 
    uart_transmit_data(&serial, "UART Initialized\n\r");

    // Initialize GPIO for LED
    gpio_init(GPIOF, &led_info);

    led_info.pin_no = PIN2;

    gpio_init(GPIOF, &led_info);
}

void loop(void) {
    // Toggle LED on PF1
    // char c = UART_Receiver(&(serial.uart));
    // if (c == '1') {
        set_high_port_pin(GPIOF, PIN1);
        delay_ms(1000); // Delay for 1 second
    //     set_low_port_pin(GPIOF, PIN2);
    //     uart_transmit_data(&serial, "RED LED ON, GREEN LED OFF\n");
    // } else if (c == '0') {
        set_low_port_pin(GPIOF, PIN1);
        delay(1000); // Delay for 1 second
    //     uart_transmit_data(&serial, "RED LED OFF, GREEN LED ON\n");
    // } else {
    //     uart_transmit_data(&serial, "RED & GREEN LED OFF\n");
    // }
    // char string[100] = "Received: ";
    // sprintf(string, "Received: %c\n", c);
    uart_transmit_data(&serial, "Hello from UART!\n\r");
    delay_ms(1000); // Delay for 1 second
}
