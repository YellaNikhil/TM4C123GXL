#ifndef SEVEN_SEGMENT_DISPLAY_H
#define SEVEN_SEGMENT_DISPLAY_H

/* 7 - Segment Display Leds are connected to PB3, PC4, PC5, PC6, PC7, PD6, PD7*/
#define LED_A (1U<<3)
#define LED_B (1U<<4)
#define LED_C (1U<<5)
#define LED_D (1U<<6)
#define LED_E (1U<<7)
#define LED_F (1U<<6)
#define LED_G (1U<<7)


/* Buttons */
#define SW1 0 // PE0
#define SW2 4 // PE4
#define SW3 5 // PA5
#define SW4 2 // PD2

void init_ports(void);

void run_seven_segment_display(void);

#endif
