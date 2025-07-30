#include <stdint.h>
#include <stdio.h>
#include <gpio_registers.h>
#include <serial.h>
#include <queue.h>

void setup(void);
void loop(void);
// void UART0_ISR(void) __attribute__((interrupt("IRQ"))); // UART0 interrupt handler

volatile char ch = 'a'; // Global variable to hold received character
// volatile queue_t rx_queue, tx_queue; // Queue to hold received characters
typedef enum{
    NO_INPUT_FROM_CONSOLE = 0,
    INPUT_RECEIVED = 1
}serial_status;

serial_status serial_input = NO_INPUT_FROM_CONSOLE; // Flag to indicate if a character has been received

char buffer_data[DATA_SIZE]; // Buffer to hold received data

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
    serial_begin(); 
    serial_println("UART Initialized\r");

    // Initialize GPIO for LED
    gpio_init(GPIOF, &led_info);
}

void loop(void) {
    // char data = serial_read(); // Read character from UART
     switch(serial_input){
        case NO_INPUT_FROM_CONSOLE:
            // No input received, do nothing
            serial_println("Hello from UART!!!\r");
            set_low_port_pin(GPIOF, PIN1);
            break;
        case INPUT_RECEIVED:
            // Process the received character
            // sprintf(buffer_data, "Received input: %c\r", ch);
            serial_println(&ch);
            set_high_port_pin(GPIOF, PIN1);
            serial_input = NO_INPUT_FROM_CONSOLE; // Reset the flag after processing
            break;
    }
    delay_ms(1000); // Delay for 1 second
}

void UART0_ISR(void){
    ch = (char)(UART0->DR & 0xff);
    UART0->ICR &= ~(0x010); // Clear receive interrupt
    serial_input = INPUT_RECEIVED; // Set the flag to indicate a character has been received
}