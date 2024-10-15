#include "i2c.h"

void hal_i2c_init(i2c_handle *i2c_handle) {
	
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
//	GPIOA->AFSEL |= SDA_PIN | SCL_PIN;  // Enable alternate functions
//	GPIOA->DEN |= SDA_PIN | SCL_PIN;     // Enable digital functions for SDA and SCL  
//	
////4. Enable the I2CSDA pin for open-drain operation. See page 676.
//	GPIOA->ODR |= SDA_PIN;               // Set SDA pin as open-drain  
	
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
	//TPR = 9
	//Write the I2CMTPR register with the value of 0x0000.0009.
	I2C1->MTPR = 0x09;      // Set the clock frequency to 100 Kbps

//10. Initiate a single byte transmit of the data from Master to Slave by writing the I2CMCS register
//with a value of 0x0000.0007 (STOP, START, RUN).

//11. Wait until the transmission completes by polling the I2CMCS register's BUSBSY bit until it has
//been cleared.

//12. Check the ERROR bit in the I2CMCS register to confirm the transmit was acknowledged.
    // Initialize I2C module 1
    
    
}

uint32_t I2C_send_data(uint8_t data, uint32_t state) {
	
	//9. Place data (byte) to be transmitted in the data register by writing the I2CMDR register with the
//desired data.
    I2C1->MDR = data;                     // Load data into the data register
	
    I2C1->MCS = state;                     // Start transmission of a single byte

    while ((I2C1->MCS & 0x01) != 0);     // Wait until the transmission is complete
	
		return I2C1->MCS & 0x0E;
}


void hal_i2c_master_tx(i2c_handle *i2c_handle, uint8_t slave_address, uint8_t *tx_buffer, uint8_t len){
	i2c_handle->i2c->MCS = MASTER_IDLE_TX_MODE;
	i2c_handle->i2c->MSA = slave_address;
	while(len-- > 0){
		i2c_handle->i2c->MDR = (*tx_buffer);
		i2c_handle->i2c->MCS = MASTER_TX_START_MODE;		
		while((i2c_handle->i2c->MCS & 0x01) != 0);
		tx_buffer++;
	}
}

void hal_i2c_master_rx(i2c_handle *i2c_handle, uint8_t slave_address, uint8_t *rx_buffer, uint8_t len){
	
}

void hal_i2c_slave_tx(i2c_handle *i2c_handle, uint8_t *tx_buffer, uint8_t len){
	
}

void hal_i2c_slave_rx(i2c_handle *i2c_handle, uint8_t *rx_buffer, uint8_t len){
	
}

void hal_i2c_handle_error_intterupt(i2c_handle *i2c_handle){
	
}

void hal_i2c_handle_evt_interrupt(i2c_handle *i2c_handle){
}
