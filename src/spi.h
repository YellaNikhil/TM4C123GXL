#ifndef _SPI_DRIVER_H_
#define _SPI_DRIVER_H_

#include "gpio_registers.h"

/* SSI Modes*/
#define SSI_MASTER_MODE 0x00
#define SSI_SLAVE_MODE_OUTPUT_ENABLED 0x04
#define SSI_SLAVE_MODE_OUTPUT_DISABLED 0x0C



typedef struct
{
  uint32_t Mode;               /*  Specifies the SPI operating mode. */
                                   

  uint32_t Direction;          /*  Specifies the SPI Directional mode state. */
                                  
  uint32_t DataSize;           /*  Specifies the SPI data size. */
                                   

  uint32_t CLKPolarity;        /*  Specifies the serial clock steady state. */
                                   

  uint32_t CLKPhase;           /*  Specifies the clock active edge for the bit capture. */
                                 

  uint32_t NSS;                /*  Specifies whether the NSS signal is managed by
                                    hardware (NSS pin) or by software using the SSI bit. */
                                  

  uint32_t BaudRatePrescaler;  /*  Specifies the Baud Rate prescaler value which will be
                                    used to configure the transmit and receive SCK clock. */
                                    

  uint32_t FirstBit;           /*  Specifies whether data transfers start from MSB or LSB bit. */
                                   
}spi_init_t;


/** 
  * @brief  SPI handle Structure definition
  */
typedef struct __spi_handle_t
{
  SSI0_Type                *Instance;       /* SPI registers base address */

  spi_init_t                   Init;          /* SPI communication parameters */

  uint8_t                    *pTxBuffPtr;     /* Pointer to SPI Tx transfer Buffer */

  uint16_t                   TxXferSize;      /* SPI Tx transfer size */
  
  uint16_t                   TxXferCount;     /* SPI Tx Transfer Counter */

  uint8_t                    *pRxBuffPtr;     /* Pointer to SPI Rx transfer Buffer */

  uint16_t                   RxXferSize;      /* SPI Rx transfer size */

  uint16_t                   RxXferCount;     /* SPI Rx Transfer Counter */

  hal_spi_state_t  State;                     /* SPI communication state */
	
}spi_handle_t;



void hal_spi_master_tx(spi_handle_t *spi_handle,uint8_t *buffer, uint32_t len);

/**
	* @brief  API used to do slave data transmission 
	* @param  *SPIx : Base address of the SPI  
  * @param  *buffer : pointer to the tx buffer 
  * @param  len : len of tx data
  * @retval none
	*/
void hal_spi_slave_tx(spi_handle_t *spi_handle, uint8_t *rcv_buffer, uint32_t len);


/**
	* @brief  API used to do master data reception 
	* @param  *SPIx : Base address of the SPI  
  * @param  *buffer : pointer to the rx buffer 
  * @param  len : len of rx data
  * @retval none
	*/
void hal_spi_master_rx(spi_handle_t*,uint8_t*, uint32_t);


/**
	* @brief  API used to do slave data reception 
	* @param  *SPIx : Base address of the SPI  
  * @param  *buffer : pointer to the rx buffer 
  * @param  len : len of rx data
  * @retval none
	*/
void hal_spi_slave_rx(spi_handle_t *spi_handle, uint8_t *rcv_buffer, uint32_t len);


/**
  * @brief  This function handles SPI interrupt request.
  * @param  hspi: pointer to a spi_handle_t structure that contains
  *                the configuration information for SPI module.
  * @retval none
  */
void hal_spi_irq_handler(spi_handle_t *hspi);




#endif
