#ifndef FULL_TANK_H
#define FULL_TANK_H
#include "gpio_registers.h"

/*GREEN led connected to PD7*/
#define GREEN_LED_ON 0x80U
#define GREEN_LED_OFF (~(GREEN_LED_ON))

/*YELLOW led connected to PC7*/
#define YELLOW_LED_ON 0x80U
#define YELLOW_LED_OFF (~(YELLOW_LED_ON))

/*NWS Button is connected to PA5*/
#define NWS 5

/*FLS Button is connected to PC6*/
#define FLS 6

void delay(uint32_t time);
void initialize_full_tank(void);
void run_full_tank(void);

#endif
