#include "ultrasonic.h"


/*Initializing the extern variables declared in Header File*/
volatile uint32_t time_travelled = 0;
volatile uint32_t rising_time = 0, falling_time = 0;


/*Static helper functions*/
static uint32_t measure_pulse_width(gpio_info *, TIMER0_Type *);
static void delay_timer0_init(void);
static void timer_init(void);
static void delay_micro_seconds(uint32_t delay);


/* Before configuring the Echo pin check which timer it uses and initialize it for capturing signal*/
void ultrasonic_init(gpio_info *echo_pin, gpio_info *trigger_pin){
	// SYSCTL->RCGCGPIO |= 0x02;
	/*Configure the trigger pin and echo pin for the ultrasonic */
	gpio_init(trigger_pin->port, trigger_pin);
	gpio_init(echo_pin->port, echo_pin);
	delay_timer0_init();
	timer_init();
}

uint32_t measure_distance(gpio_info *echo_pin, TIMER0_Type *timer){
	uint32_t distance = 0;
	time_travelled = measure_pulse_width(echo_pin, timer);
	distance = (time_travelled*10625)/10000000;
	return distance;
}

static uint32_t measure_pulse_width(gpio_info *echo_pin, TIMER0_Type *timer){
	while(1){
		timer->ICR = 4;            /* clear timer0A capture flag */
		while((timer->RIS & 4) == 0) ;    /* wait till captured */
		if((echo_pin->port)->DATA & (1<<6)){ /*check if rising edge occurs */
			rising_time = timer->TAR;     /* save the timestamp */
			/* detect falling edge */
			timer->ICR = 4;            /* clear timer0A capture flag */
			while((timer->RIS & 4) == 0) ;    /* wait till captured */
			falling_time = timer->TAR;     /* save the timestamp */
			time_travelled  = falling_time - rising_time; /* return the time difference */
			return time_travelled;
		}
	}
}


static void delay_timer0_init(void){
//	1. Ensure the timer is disabled (the TnEN bit is cleared) before making any changes.
	SYSCTL->RCGCTIMER |= 1;
	TIMER0->CTL &= (~(1ul << 0));
//	2. Write the GPTM Configuration (GPTMCFG) register with a value of 0x0000.0004.

	TIMER0->CFG = 4; // special mode enabled
	
// 3. In the GPTM Timer Mode (GPTMTnMR) register, write the TnCMR field to 0x1 and the TnMR
// field to 0x3 and select a count direction by programming the TnCDIR bit.
		
	TIMER0->TAMR = 0x17; // capture mode enabled.
	
// 4. Configure the type of event that the timer captures by writing the TnEVENT field of the GPTM
//Control (GPTMCTL) register.
	TIMER0->CTL |= (1<<3) | (1<<2);
	
//5. If a prescaler is to be used, write the prescale value to the GPTM Timer n Prescale Register
//(GPTMTnPR).
	//TIMER0->TAPR = 0; // Prescaler
	
	
//6. Load the timer start value into the GPTM Timer n Interval Load (GPTMTnILR) register.
	//TIMER0->TAILR = 0;

//7. If interrupts are required, set the CnEIM bit in the GPTM Interrupt Mask (GPTMIMR) register.
	// TIMER0->IMR |= (0x04); // Interrupt is enabled

//8. Set the TnEN bit in the GPTM Control (GPTMCTL) register to enable the timer and start counting.
	TIMER0->CTL |= (1<<0);	
	
	// NVIC->ISER[0] |= (1 << TIMER0A_IRQn); // Enable Interrupt Sub Routine(ISR) for timer.
}

static void timer_init(void){
	SYSCTL->RCGCTIMER |= 2;  /*enable clock Timer1 subtimer A in run mode */
	TIMER1->CTL = 0; /* disable timer1 output */
	TIMER1->CFG = 0x4; /*select 16-bit configuration option */
	TIMER1->TAMR = 0x02; /*select periodic down counter mode of timer1 */
	TIMER1->TAILR = 0; /* TimerA counter starting count down value  */
	TIMER1->TAPR = 16 - 1; // Setting a pre-scaler value
	TIMER1->ICR = 0x1;          /* TimerA timeout flag bit clears*/
	TIMER1->CTL |= 0x03;        /* enable Timer A after initialization */
}


static void delay_micro_seconds(uint32_t delay){
		TIMER1->TAILR = delay - 4;  
		TIMER1->ICR = 0x1;
		while((TIMER1->RIS & 0x1) == 0);
}

