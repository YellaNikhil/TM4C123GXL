#include "lcd_raw.h"
#include<stdlib.h>
#include<string.h>

// static gpio_info db[8], rs, rw, enable;
static void set_data(const lcd_info*, uint8_t data);

static uint8_t hex_of_characters[256];

uint8_t _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
uint8_t _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
uint8_t _displayfunction = LCD_4BITMODE | LCD_2LINE | LCD_5x8DOTS;

void lcd_init(const lcd_info *lcd){
	// SYSCTL->RCGCGPIO |= 0x1B;
	
	/*Initializing the GPIO port pins*/
	for(int i=0;i<8;i++){
		gpio_init(lcd->databits[i].port, &(lcd->databits[i]));
	}

	/*Initializing the RS, RW & EN pins*/
	gpio_init(lcd->rs.port, &(lcd->rs));
	gpio_init(lcd->rw.port, &(lcd->rw));
	gpio_init(lcd->enable.port, &(lcd->enable));
	
	delay_ms(10);
	
	/*Initializing the LCD*/
	lcd_cmd(lcd, BIT_8_MODE_SET | TWO_LINE_MODE | FIVE_EIGHT_DISPLAY_MODE);
	lcd_cmd(lcd, ENTRY_MODE);
	lcd_cmd(lcd, DISPLAY_ON | CURSOR_ON);
	clear_screen(lcd);
	
	/* Declaration of hex values to Characters */
	uint8_t hex_value = 65;
	while(hex_value <= 'Z'){
		hex_of_characters[hex_value] = hex_value;
		hex_value++;
	}
	hex_value = 97;
	while(hex_value <='z'){
		hex_of_characters[hex_value] = hex_value;
		hex_value++;
	}
}
	
void print_char(const lcd_info *lcd, char ch){
		set_data(lcd, ch);
		set_high_port_pin(lcd->rs.port, lcd->rs.pin_no);/* Set high for Data Mode */
		set_low_port_pin(lcd->rw.port, lcd->rw.pin_no);/* Write to LCD*/
		set_high_port_pin(lcd->enable.port, lcd->enable.pin_no);
		delay_ms(10);
		set_low_port_pin(lcd->enable.port, lcd->enable.pin_no);
}

void print(const lcd_info *lcd, const char *data){
	uint32_t size = strlen(data);
	uint32_t index = 0;
	while(index < size){
		print_char(lcd, data[index]);
		index++;
	}
}

void lcd_cmd(const lcd_info *lcd, char cmd){
	set_data(lcd, (uint8_t)cmd);
	set_low_port_pin(lcd->rs.port, lcd->rs.pin_no);
	set_low_port_pin(lcd->rw.port,lcd->rw.pin_no);
	set_high_port_pin(lcd->enable.port, lcd->enable.pin_no);
	delay_ms(10);
	set_low_port_pin(lcd->enable.port, lcd->enable.pin_no);
}

void clear_screen(const lcd_info *lcd){
	set_data(lcd, 1);
	set_low_port_pin(lcd->rs.port, lcd->rs.pin_no);
	set_low_port_pin(lcd->rw.port, lcd->rw.pin_no);
	set_high_port_pin(lcd->enable.port, lcd->enable.pin_no);
	delay_ms(10);
	set_low_port_pin(lcd->enable.port, lcd->enable.pin_no);
}


static void set_data(const lcd_info *lcd, uint8_t data){
	for(int i=0;i<8;i++){
		uint8_t value = (uint8_t)(1 << i);
		if((value & data)){
			set_high_port_pin(lcd->databits[i].port, lcd->databits[i].pin_no);
		}
		else{
			set_low_port_pin(lcd->databits[i].port, lcd->databits[i].pin_no);
		}
	}
}
	
