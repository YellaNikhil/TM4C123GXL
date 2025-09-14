#ifndef OVER_FLOW_TANK_H
#define OVER_FLOW_TANK_H

#include "full_tank.h"


/*RED led connected to PD6*/
#define RED_LED_ON  0x40U
#define RED_LED_OFF (~(RED_LED_ON))

/* OFS is connected to PA2 Pin */
#define OFS 2

void init_over_flow_tank(void);
void run_over_flow_tank(void);

#endif
