#ifndef LCD_RAW_H
#define LCD_RAW_H

#include<TM4C123GH6PM.h>
#include<stdint.h>

#include "gpio_registers.h"


/* Instruction used for Arduino Library */
// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x11DOTS 0x04
#define LCD_5x8DOTS 0x00

//// flags for backlight control
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00

//#define EN b00000100  // Enable bit
//#define RW b00000010  // Read/Write bit
//#define RS b00000001  // Register select bit

#define EN 0x04 // Enable bit
#define RW 0x02  // Read/Write bit
#define RS 0x01  // Register select bit


/*Instruction Set Declarations*/

/*Clear Display*/
#define CLEAR_FLAG 0x01

/*Return Home Instruction*/
#define RETURN_HOME 0x02

/*Entry Mode Set */
#define ENTRY_MODE_INCREMENT 0x06 // 3
#define ENTRY_MODE_DECREMENT 0x04 // 2
#define ENTRY_MODE_READ ENTRY_MODE_DECREMENT // 1
#define ENTRY_MODE ENTRY_MODE_INCREMENT
#define ENTIRE_DISPLAY_SHIFT_LEFT 0x07
#define ENTIRE_DISPLAY_SHIFT_RIGHT 0x05

/*Display ON/OFF Control */
#define DISPLAY_ON 0x0C
#define CURSOR_ON 0x0A
#define CURSOR_BLINK_ON 0x09
#define DISPLAY_OFF 0x0B
#define CURSOR_OFF 0x0D
#define CURSOR_BLINK_OFF 0x0E

/*Cursor or Display Shift*/
#define CURSOR_LEFT_SHIFT 0x10
#define CURSOR_RIGHT_SHIFT 0x14
#define DISPLAY_LEFT_SHIFT 0x18
#define DISPLAY_RIGHT_SHIFT 0x1C

/*Function Set */
#define BIT_8_MODE_SET 0x30
#define BIT_4_MODE_SET 0x20
#define ONE_LINE_MODE 0x20
#define TWO_LINE_MODE 0x28
#define FIVE_EIGHT_DISPLAY_MODE 0x20
#define FIVE_ELEVEN_DISPLAY_MODE 0x24

/*Set CGRAM Address*/
#define SET_CGRAM(x) (0x40 | x)

/*Set DDRAM Address*/
#define SET_POS_FIRST_LINE(x) (0x80 | x)
#define SET_POS_SECOND_LINE(x) (0x80 | (x + 0x40))

typedef struct{
	uint32_t entry_mode;
	uint32_t display_mode;
	uint32_t lines;
	uint32_t cursor;
	uint32_t cursor_blink;
	gpio_info rs;
	gpio_info rw;
	gpio_info enable;
	gpio_info databits[8];	
}lcd_info;

extern uint8_t _displaycontrol;
extern uint8_t _displaymode;
extern uint8_t _displayfunction;


void lcd_init(const lcd_info *);
void print_char(const lcd_info *, char);
void print(const lcd_info *, const char *);
void clear_screen(const lcd_info *);
void lcd_cmd(const lcd_info *, char cmd);

#endif
