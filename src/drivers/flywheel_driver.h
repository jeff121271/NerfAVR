/**
 *  flywheel_driver.h
 *
 *  Interface file for the flywheel driver.
 *
 *  Jeff Campbell
 *  2/15/18
 *
 */

#ifndef FLYWHEEL_DRIVER_H
#define FLYWHEEL_DRIVER_H

/* Includes */
#include <stdint.h>
#include <stdbool.h>

/* Defines */

/* Proportional gain of flywheel PID */
#define FLYWHEEL_PID_P 10u

/* Integral gain of flywheel PID */
#define FLYWHEEL_PID_I 5u

/* Differential gain of flywheel PID */
#define FLYWHEEL_PID_D 1u

/* Value to select flywheel #1 */
#define FLYWHEEL_SELECT_1 1u

/* Value to select flywheel #2 */
#define FLYWHEEL_SELECT_2 2u

/* Time, in ms, between adjustments to slave PWM */
#define FLYWHEEL_ADJUST_TIME_MS 250u

/* Time, in ms, between speed calculations */
#define FLYWHEEL_CALCULATION_TIME_MS 1000u

/* Enumeration of flywheel driver states */
typedef enum flywheel_states
{
    FLY_STATE_INIT = 0,     /* Init state */
    FLY_STATE_IDLE,         /* Idle state - no command */
    FLY_STATE_RAMP_UP,      /* Ramp up state - spin both motors up to speed */
    FLY_STATE_MAINTAIN      /* Maintain state - try to match slave speed to master speed */
} flywheel_states_t;

/* Global Functions */
extern void gvFlywheel_process(uint16_t uwCallRateMs);
extern void gvFlywheel_intHandler(uint8_t ubSelect);
extern bool gfFlywheel_engaged(void);

#endif /* #ifndef FLYWHEEL_DRIVER_H */