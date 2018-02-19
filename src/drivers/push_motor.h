/**
 *  push_motor.h
 *
 *  Interface file for push_motor.c.
 *
 *  Jeff Campbell
 *  2/15/18
 *
 */

#ifndef PUSH_MOTOR_H
#define PUSH_MOTOR_H

/* Includes */

/* Defines */

/* Time to wait between shots if trigger is held */
#define PUSH_COOLDOWN_MS 500u

/* Timeout, in ms, of a push extend or retract */
#define PUSH_OPERATION_TIMEOUT_MS 1000u

/* Enumeration of push motor states */
typedef enum push_motor_state
{
    PUSH_STATE_INIT = 0,    /* < Init state */
    PUSH_STATE_WAIT,        /* < Waiting state */
    PUSH_STATE_EXTEND,      /* < Extending state */
    PUSH_STATE_RETRACT      /* < Retracting state */
} push_motor_state_t;

/* Global Functions */
extern void gvPush_process(uint16_t uwCallRateMs);
extern void gvPush_setCmd(push_motor_state_t eCmd);

#endif /* #ifndef PUSH_MOTOR_H */