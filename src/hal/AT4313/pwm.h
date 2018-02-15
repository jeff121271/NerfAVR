/**
 *  pwm.h
 *
 *  Interface file for pwm.c.
 *
 *  Jeff Campbell
 *  2/15/18
 *
 */

#ifndef PWM_H
#define PWM_H

/* Includes */

/* Defines */

/* Max value of the 8-bit compare register */
#define PWM_MAX_COMP_VALUE 255u

/* Max possible command as a percentage */
#define PWM_MAX_CMD 100u

/* Global Functions */
extern void gvPWM_init(void);
extern void gvPWM_setCmd1(uint8_t ubCmd);
extern void gvPWM_setCmd2(uint8_t ubCmd);

#endif /* #ifndef PWM_H */