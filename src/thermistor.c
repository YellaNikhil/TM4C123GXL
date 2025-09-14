#include "thermistor.h"

// static double temp = 0.0;

void init_thermistor(void){
  /* Enable Clock to ADC0 and GPIO pins*/
	SYSCTL->RCGCGPIO |= (1U << 4);   /* Enable Clock to GPIOE or PE3/AN0 */ 
	SYSCTL->RCGCADC |= MASK(ADC_NUM);        //activate ADC0 clock
    
  /* initialize PE3 for AIN0 input*/
	GPIOE->DIR &= ~MASK(ADC_SS);		/* PE3 as input*/
	GPIOE->AFSEL |= MASK(ADC_SS);    /* enable alternate function */
	GPIOE->DEN &= ~MASK(ADC_SS);    /* disable digital function */
  GPIOE->AMSEL |= MASK(ADC_SS);       /* enable analog function */
   
	/* initialize sample sequencer3 */
	ADC0->ACTSS &= ~MASK(ADC_SS);        /* disable SS3 during configuration */
	ADC0->EMUX &= ~((uint32_t)(0xF000));   /* software trigger conversion */
  	ADC0->SSMUX3 = 0;         		     /* get input from channel 0 */
	ADC0->SSCTL3 |= (MASK(1)|MASK(2));  /* take one sample at a time, set flag at 1st sample */
  ADC0->ACTSS |= MASK(ADC_SS);         /* enable ADC0 sequencer 3 */
   
}


void MeasureTemp(void)
{
	double n = 0.0;
	double Rtherm = 0.0;
	double ratio=0.0;
	
	ADC0->PSSI |= MASK(ADC_SS);  /* Enable SS3 conversion or start sampling data from AN0 */
	while((ADC0->RIS & 0x08) == 0) /* Wait until sample conversion completed*/
	{
				
	}   
  n = ADC0->SSFIFO3&0xFFF;		     /* read adc conversion result from SS3 FIFO*/
  ADC0->ISC |= MASK(ADC_SS);          /* clear conversion clear flag bit*/
	
	//calculate the resistor value of temperature sensor
	Rtherm = R1 * (((N) / (n)) -1);
	
	ratio = (Rtherm / Rerf);
	
	//calculate temperature (when > 25 celsius)
	temp = (1.0/(A2 + B2*log(ratio) + C2*pow(log(ratio),2) + D2*pow(log(ratio), 3))) -273.15;
	
}
