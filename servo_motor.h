#ifndef SERVO_MOTOR_H
#define SERVO_MOTOR_H

#include <TM4C123GH6PM.h>

#include <stdint.h>

#define SERVO_PIN (1<<2)
#define SERVO_FREQUENCY 50
#define SERVO_DEGREES_BASE 38000
#define SERVO_DEGREES_CHAGE_ONE 11
#define SERVO_DEGREES_0 (SERVO_DEGREES_BASE)
#define SERVO_DEGREES_45 (SERVO_DEGREES_BASE - 500)
#define SERVO_DEGREES_90 (SERVO_DEGREES_BASE - 1000)
#define SERVO_DEGREES_180 (SERVO_DEGREES_BASE - 2000)
#define SERVO_DEGREES_CHANGE(x) (SERVO_DEGREES_BASE - (x*SERVO_DEGREES_CHAGE_ONE))


/* Clock Configuration for RCC */
#define OSCSRC_MOSC (0x0 << 4)
#define OSCSRC_PIOSC (0x1 << 4)
#define OSCSRC_PIOSC_4MHZ (0x2 << 4)
#define OSCSRC_LFIOSC (0x3 << 4)

/*Use PWMDIV */
#define USEPWMDIV() (SYSCTL->RCC |= (1 << 20))
#define PWMDIV_2()  (SYSCTL->RCC &= (~(0x7UL << 17)))
#define PWMDIV_4()  (SYSCTL->RCC & = (~(0x6UL << 17)))
#define PWMDIV_8()  (SYSCTL->RCC |= (~(0x5UL << 17)))
#define PWMDIV_16()  (SYSCTL->RCC |= (~(0x4UL << 17)))
#define PWMDIV_32()  (SYSCTL->RCC |= (~(0x3UL << 17)))
#define PWMDIV_64()  (SYSCTL->RCC |= (~(0x2UL << 17)))

void init_servo_motor(void);
void run_servo_motor(void);
void turn_servo_degrees_0(void);
void turn_servo_degrees_45(void);
void turn_servo_degrees_90(void);
void turn_servo_degrees_180(void);
void turn_servo_degrees(uint32_t);

#endif
