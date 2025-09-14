#include <stdint.h>
#include <math.h>
#include<TM4C123GH6PM.h>

#define MASK(x)   (1UL<<x)
#define ADC_NUM   (0)  // ADC0
#define ADC_SS		(3)


#define Rerf (10000)  //Reference resistor for calculation of temperature
#define R1   (5100)	 //Resistor connecting sensor
#define N (4096)    //Resolution of ADC (2^12)

//room temperature less than 25 
#define A1 (3.354016E-03)
#define B1 (2.909670E-04)
#define C1 (1.632136E-06)
#define D1 (7.192200E-08)

//room temperature greater than 25
#define A2 (3.354016E-03)
#define B2 (2.933908E-04)
#define C2 (3.494314E-06)
#define D2 (-7.712690E-07)

static double temp = 0.0;

void init_thermistor(void);
void MeasureTemp(void);
