#include <stdint.h>
#include "gpio_registers.h"

void setup(void);
void loop(void);

int main(void) {
    setup();
    while(1){
        loop();
    }
    return 0;
}

void setup(void) {
    // Initialize GPIO Port F
    GPIOF_CLK_ENABLE();
    init_sys_tick_timer();
    
    gpio_info led_info = {
        .port = GPIOF,
        .pin_no = PIN1, // Using PF1 for LED
        .digital_enable = 1,
        .optype = OUTPUT,
        .pulltype = 0, // No pull-up or pull-down
        .alternate_enable = 0,
        .alternate_function = ALT_FUNC_ANALOG_MODE
    };
    
    gpio_init(GPIOF, &led_info);
}

void loop(void) {
    // Toggle LED on PF1
    set_high_port_pin(GPIOF, PIN1);
    delay_ms(500);
    set_low_port_pin(GPIOF, PIN1);
    delay_ms(500);
}
