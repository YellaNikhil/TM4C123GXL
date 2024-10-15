#ifndef _I2C_H_
#define _I2C_H_


/*Libraries */
#include "gpio_registers.h"

//Master Control Status 
#define ENABLE_MODE 0x01
#define START_MODE 0x03
#define STOP_MODE 0x04
#define START_RX_NO_ACK_MODE 0x03
#define START_TX_STOP_MODE 0x07
#define START_RX_STOP_MODE 0x07
#define START_RX_MODE 0x0B

// Current Master IDLE State to after state
#define MASTER_IDLE_TX_MODE START_MODE
#define MASTER_IDLE_TX_IDLE_MODE START_TX_STOP_MODE
#define MASTER_IDLE_RX_IDLE_MODE START_TX_STOP_MODE
#define MASTER_IDLE_RX_MODE START_RX_MODE
#define MASTER_IDLE_RX_NO_ACK_MODE START_MODE

// Current Master Transmit States and after states
#define MASTER_TX_MODE ENABLE_MODE
#define MASTER_TX_IDLE_MODE STOP_MODE
#define MASTER_TX_TX_IDLE_MODE 0x05
#define MASTER_TX_START_MODE START_MODE
#define MASTER_TX_START_TX_IDLE_MODE START_TX_STOP_MODE
#define MASTER_TX_START_RX_NO_ACK_MODE START_MODE
#define MASTER_TX_START_RX_MODE START_RX_MODE


// Current Master Receive States and after states
#define MASTER_RX_NO_ACK_MODE START_RX_MODE
#define MASTER_RX_IDLE_MODE STOP_MODE
#define MASTER_RX_RX_IDLE_MODE 0x05
#define MASTER_RX_RX_MODE 0x09
#define MASTER_RX_START_RX_NO_ACK START_MODE
#define MASTER_RX_START_RX_IDLE_MODE START_RX_STOP_MODE
#define MASTER_RX_START_RX_MODE START_RX_STOP_MODE


/*Data Structures for I2C */
typedef enum{
	I2C_STATE_RESET    = 0x00,
	I2C_STATE_READY    = 0X01,  
	I2C_STATE_BUSY     = 0X02,
	I2C_STATE_BUSY_TX  = 0X03,
	I2C_STATE_BUSY_RX  = 0X04,
	I2C_STATE_ERROR    = 0X05
}i2c_state;

typedef struct {
	uint32_t ClockSpeed;
	
	uint32_t DutyCycle;
	
	uint32_t OwnAddress1;
	
	uint32_t AddressingMode;
	
	uint32_t DualaddressMode;
	
	uint32_t OwnAddress2;
	
	uint32_t GeneralCallMode;
	
	uint32_t NoStretchMode;
	
	uint32_t ack_enable;
	
}i2c_init;

typedef struct{
	I2C0_Type *i2c;
	
	i2c_init Init;
	
	uint8_t *pBuffPtr;
	
	uint32_t XfferSize;
	
	volatile uint32_t XfferCount;
	
	i2c_state State;
	
	uint32_t ErrorCode;
	
}i2c_handle;

void i2c_master_tx(void);

void i2c_master_rx(void);

void hal_i2c_init(i2c_handle *i2c_handle);

void hal_i2c_master_tx(i2c_handle *i2c_handle,uint8_t slave_address, uint8_t *tx_buffer, uint8_t len);

void hal_i2c_master_rx(i2c_handle *i2c_handle, uint8_t slave_address, uint8_t *rx_buffer, uint8_t len);

void hal_i2c_slave_tx(i2c_handle *i2c_handle, uint8_t *tx_buffer, uint8_t len);

void hal_i2c_slave_rx(i2c_handle *i2c_handle, uint8_t *rx_buffer, uint8_t len);

void hal_i2c_handle_error_intterupt(i2c_handle *i2c_handle);

void hal_i2c_handle_evt_interrupt(i2c_handle *i2c_handle);

uint32_t I2C_send_data(uint8_t data, uint32_t state);

#endif
