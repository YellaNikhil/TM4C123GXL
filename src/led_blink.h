#ifndef LED_BLINK_H
#define LED_BLINK_H

#include<TM4C123GH6PM.h>

#define LED_ON 0x0EUL
#define LED_OFF (~(LED_ON))


void init_led(void);

void blink_led(void);

#endif
