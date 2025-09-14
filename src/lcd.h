#ifndef LCD_H
#define LCD_H


#include<stdint.h>
#include<TM4C123GH6PM.h>

#include "gpio_registers.h"

#define SDA_PIN 0x80   // GPIO pin for Serial Data (SDA)
#define SCL_PIN 0x40   // GPIO pin for Serial Clock (SCL)
#define LCD_SLAVE_ADDRESS 0x27
#define LCD_CONTROL_RUN_MODE 0x80
#define LCD_CONTROL_STOP_MODE 0x00
#define LCD_COMMAND_MODE 0x00
#define LCD_DATA_MODE 0x40

// void delayMs(int n);

void LCD_init(void);
void LCD_writeChar(char ch);
void LCD_writeString(const char *);
// void begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS );
void LCD_clear(void);
void LCD_home(void);
void LCD_no_display(void);
void LCD_display(void);
void LCD_no_blink(void);
void LCD_blink(void);
void LCD_no_cursor(void);
void LCD_cursor(void);
void LCD_scroll_display_left(void);
void LCD_scroll_display_right(void);
void LCD_print_left(void);
void LCD_print_right(void);
void LCD_print(const char *);
void LCD_left_to_right(void);
void LCD_right_to_left(void);
void LCD_shift_increment(void);
void LCD_shift_decrement(void);
void LCD_no_backlight(void);
void LCD_backlight(void);
void LCD_autoscroll(void);
void LCD_no_autoscroll(void); 
void LCD_create_char(uint8_t, uint8_t[]);
//void LCD_create_char(uint8_t location, const char *charmap);
  // Example: 	const char bell[8] PROGMEM = {B00100,B01110,B01110,B01110,B11111,B00000,B00100,B00000};
void LCD_set_cursor(uint8_t, uint8_t); 

// void delayMs(int);

#endif
