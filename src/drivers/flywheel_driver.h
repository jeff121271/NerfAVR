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

/* Defines */

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

#endif /* #ifndef FLYWHEEL_DRIVER_H */