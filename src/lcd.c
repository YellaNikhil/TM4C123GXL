#include "lcd.h"
#include "lcd_raw.h"
#include "i2c.h"


static void set_read_write(uint8_t mode){
	if(mode == 0){
		I2C1->MSA &= ~(1ul << 0);
	}
	else{
		I2C1->MSA |= (1 << 0);
	}
}

static void write4bits(uint8_t value);
static void transmission_enable(uint8_t value);
static void LCD_send_data(uint8_t , uint8_t);
static void command(uint8_t command);
static void I2C_init(void);

static void I2C_init(void) {
	  init_sys_tick_timer();
//1. Enable the I2C clock using the RCGCI2C register in the System Control module (see page 348).
		SYSCTL->RCGCI2C |= 0x02;  // Enable the I2C module 1 clock
	
// There must be a delay of 3 system clocks after the I2C module clock is enabled before
// any I2C module registers are accessed
		delay_ms(10);
	
//2. Enable the clock to the appropriate GPIO module via the RCGCGPIO register in the System
//Control module (see page 340). To find out which GPIO port to enable, refer to Table
//23-5 on page 1351.
	SYSCTL->RCGCGPIO |= 0x01; // Enable the GPIO Port A clock
	
//3. In the GPIO module, enable the appropriate pins for their alternate function using the
//GPIOAFSEL register (see page 671). To determine which GPIOs to configure, see Table
//23-4 on page 1344.
	GPIOA->DEN |= SDA_PIN | SCL_PIN;     // Enable digital functions for SDA and SCL  
	GPIOA->AFSEL |= SDA_PIN | SCL_PIN;  // Enable alternate functions
	
//4. Enable the I2CSDA pin for open-drain operation. See page 676.
	GPIOA->ODR |= SDA_PIN;               // Set SDA pin as open-drain  
	
//5. Configure the PMCn fields in the GPIOPCTL register to assign the I2C signals to the appropriate
//pins. See page 688 and Table 23-5 on page 1351.
	GPIOA->PCTL &= ~(0xFF000000);				// Clear bits for SDA & SCL  Pin.
	GPIOA->PCTL |= (0x33 << 24);        // Assign I2C signals to pins
	
//6. Initialize the I2C Master by writing the I2CMCR register with a value of 0x0000.0010.
	I2C1->MCR = 0x10;       // Enable I2C master function

//7. Set the desired SCL clock speed of 100 Kbps by writing the I2CMTPR register with the correct
//value. The value written to the I2CMTPR register represents the number of system clock periods
//in one SCL clock period. The TPR value is determined by the following equation:
//TPR = (System Clock/(2*(SCL_LP + SCL_HP)*SCL_CLK))-1;
//TPR = (20MHz/(2*(6+4)*100000))-1;
//TPR = 9;
//Write the I2CMTPR register with the value of 0x0000.0009.
	I2C1->MTPR = 0x07;      // Set the clock frequency to 100 Kbps
  
	
	I2C1->MSA = (LCD_SLAVE_ADDRESS << 1);
	set_read_write(0);		
}

void LCD_init(void) {
	I2C_init();
	// SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
	// according to datasheet, we need at least 40ms after power rises above 2.7V
	// before sending commands. Arduino can turn on way befer 4.5V so we'll wait 50
  delay_ms(50);
	
	// Now we pull both RS and R/W low to begin commands
	I2C_send_data(LCD_BACKLIGHT, MASTER_IDLE_TX_IDLE_MODE);  
	delay_ms(DELAY_MS_1000);


	// Setting the display to 8 bit mode and waiting with certain delay according to datasheet.
	// do this 3 times as mentioned in detailed datasheet Page No. 45 Figure 23
	/* We are using write4bits instead of send_data because first the I2C needs to be configured
	how we would communicate with 4bit or 8 bit mode i2c communication */
  write4bits(LCD_FUNCTIONSET | LCD_8BITMODE);  // 8-bit MODE
	delay_ms(5); // Need to wait 4.1 ms but made it to 10 ms.

	write4bits(LCD_FUNCTIONSET | LCD_8BITMODE);
	delay_ms(5);

	write4bits(LCD_FUNCTIONSET | LCD_8BITMODE); 
	delay_ms(1);

	write4bits(LCD_FUNCTIONSET | LCD_4BITMODE);

	// Setting the LCD to 2 lines and 5*8 character mode
	command(LCD_FUNCTIONSET | _displayfunction);


	_displaycontrol = LCD_DISPLAYCONTROL | LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
	LCD_display();
	
	LCD_clear();
	
	_displaymode = LCD_ENTRYMODESET | LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
	command(_displaymode);
	
	LCD_home();
}


//void I2C_send(uint8_t slave_addr, uint8_t data) {
//    I2C1->MSA = (slave_addr << 1) | 0x0u;   // Configure slave address and set write mode
//    I2C1->MDR = data;                     // Load data into the data register
//    I2C1->MCS = 0x03;                     // Start transmission of a single byte

//    while ((I2C1->MCS & 0x01) != 0);     // Wait until the transmission is complete
//}

static void LCD_send_data(uint8_t value, uint8_t mode) {
	uint8_t highnib = value & 0xf0;
	uint8_t lownib = (value<<4) & 0xf0;
	write4bits((highnib) | mode);
	write4bits((lownib)| mode);
}



void LCD_writeChar(char ch) {
		// I2C_send_data(LCD_CONTROL_STOP_MODE | LCD_DATA_MODE, MASTER_IDLE_TX_MODE); // Send the control byte with data mode set.
    I2C_send_data(ch, MASTER_IDLE_TX_IDLE_MODE);  // Send the data byte and stop the I2C.
    delay_ms(2); // Delay for the LCD to process the data
}

void LCD_writeString(const char *str) {
    while (*str) {
        LCD_writeChar(*str++);
    }
}

void LCD_clear(void){
	command(LCD_CLEARDISPLAY);// clear display, set cursor position to zero
	delay_ms(2);  // this command takes a long time!
//   if (_oled) setCursor(0,0);
}
void LCD_home(void){
	command(LCD_RETURNHOME);  // set cursor position to zero
	delay_ms(2);  // this command takes a long time!
}
void LCD_no_display(void){
	_displaycontrol &= ~LCD_DISPLAYON;
	command(_displaycontrol);
}
void LCD_display(void){
	_displaycontrol |= LCD_DISPLAYON;
	command(_displaycontrol);
}

void LCD_no_blink(void){
	_displaycontrol &= ~(LCD_BLINKON);
	command(_displaycontrol);
}

void LCD_blink(void){
	_displaycontrol |= LCD_BLINKON;
	command(_displaycontrol);
}

void LCD_no_cursor(void){
	_displaycontrol &= ~LCD_CURSORON;
	command(_displaycontrol);
}

void LCD_cursor(void){
	_displaycontrol |= LCD_CURSORON;
	command(_displaycontrol);
}

void LCD_scroll_display_left(void){
	command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

void LCD_scroll_display_right(void){
	command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

void LCD_print_left(void){

}

void LCD_print_right(void){
}

static void write4bits(uint8_t value){
	value = value | LCD_BACKLIGHT;
	I2C_send_data(value, MASTER_IDLE_TX_IDLE_MODE);  // Sending data byte and stopping the i2c.
	transmission_enable(value);
}

static void transmission_enable(uint8_t value){
	I2C_send_data(value | EN, MASTER_IDLE_TX_MODE);
	delay_us(1);
	
	I2C_send_data(value & ~EN, MASTER_TX_TX_IDLE_MODE);
	delay_us(50);
}

static void command(uint8_t command){
	// I2C_send_data(LCD_CONTROL_STOP_MODE | LCD_COMMAND_MODE, MASTER_IDLE_TX_MODE); // Sending control byte
  LCD_send_data(command, 0); // Send command data to LCD.
}

void LCD_print(const char string[]){
	int index = 0;
	while(string[index] != '\0'){
		LCD_send_data(string[index], RS);
		index++;
	}
}
void LCD_left_to_right(void){
	_displaymode |= LCD_ENTRYLEFT;
	command(_displaymode);
}

void LCD_right_to_left(void){
	_displaymode &= ~LCD_ENTRYLEFT;
	command(_displaymode);
}

void LCD_shift_increment(void){

}

void LCD_shift_decrement(void){
	
}

void LCD_no_backlight(void){
	command(LCD_NOBACKLIGHT);
}

void LCD_backlight(void){
	// command(LCD_BACKLIGHT);
//	write4bits(0x00);
	I2C_send_data(LCD_BACKLIGHT, MASTER_IDLE_TX_IDLE_MODE);
}

void LCD_autoscroll(void){
	_displaymode |= LCD_ENTRYSHIFTINCREMENT;
	command(_displaymode);
}

void LCD_no_autoscroll(void){
 	_displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
	command(_displaymode);
}

void LCD_create_char(uint8_t value, uint8_t arr[]){
//	uint8_t location &= 0x7; // we only have 8 locations 0-7
//	command(SET_POS_FIRST_LINE(location << 3));
//	for (int i=0; i<8; i++) {
//		write(charmap[i]);
//	}
}

//void LCD_create_char(uint8_t location, const char *charmap){
//}
  // Example: 	const char bell[8] PROGMEM = {B00100,B01110,B01110,B01110,B11111,B00000,B00100,B00000};
void LCD_set_cursor(uint8_t row, uint8_t col){
//	int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
	// if ( row > _numlines ) {
	// 	row = _numlines-1;    // we count rows starting w/0
	// }
	if(row == 0){
		// command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
		command(SET_POS_FIRST_LINE(col));
	}
	else{
		command((0x80 | (col + 0x40)));
	}
} 
