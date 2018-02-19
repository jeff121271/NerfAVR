/**
 *  push_motor.c
 *
 *  Driver for the push motor which pushes the darts
 *  into the chamber.
 *
 *  Push Motor Scheme:
 *      PIN_PUSH_CMD_1 -> PHASE     (0 for forward, 1 for reverse)
 *      PIN_PUSH_CMD_2 -> ENABLE    (Technically a PWM, but should work with 100% duty cycle)
 *
 *  Jeff Campbell
 *  2/15/18
 *
 */

/* Includes */
#include <stdint.h>
#include "pins.h"
#include "flywheel_driver.h"
#include "push_motor.h"

/* Prototypes */
void gvPush_process(uint16_t uwCallRateMs);

/* Local Variables */

/**
 *  void gvPush_process(uint16_t uwCallRateMs)
 *
 *  Description:
 *      Processes the state machine governing the
 *      dart push motor.
 *
 *  Parameters:
 *      uwCallRateMs = Call rate of this function, in ms
 *
 *  Returns:
 *      N/A
 *
 */
void gvPush_process(uint16_t uwCallRateMs)
{
    static push_motor_state_t seState = PUSH_STATE_INIT;
    static uint16_t suwTimerMs = 0u;
    static uint16_t suwCooldownTimerMs = 0u;

    /* Increment timer */
    suwTimerMs += uwCallRateMs;

    /* Process state actions */
    switch (seState)
    {
        case PUSH_STATE_INIT:
            /* Do nothing */
            break;

        case PUSH_STATE_WAIT:
            /* Disable motor */
            gvPins_control(PIN_PUSH_CMD_2, PIN_LOGIC_LOW);

            /* Clear timer */
            suwTimerMs = 0u;

            /* Increment cooldown timer */
            suwCooldownTimerMs += uwCallRateMs;
            break;

        case PUSH_STATE_EXTEND:
            /* Set phase to extend */
            gvPins_control(PIN_PUSH_CMD_1, PIN_LOGIC_LOW);

            /* Enable motor */
            gvPins_control(PIN_PUSH_CMD_2, PIN_LOGIC_HIGH);
            break;

        case PUSH_STATE_RETRACT:
            /* Set phase to retract */
            gvPins_control(PIN_PUSH_CMD_1, PIN_LOGIC_HIGH);

            /* Enable motor */
            gvPins_control(PIN_PUSH_CMD_2, PIN_LOGIC_HIGH);
            break;

        default:
            /* Do nothing */
            break;
    }

    /* Process state transitions */
    switch (seState)
    {
        case PUSH_STATE_INIT:
            /* Move to wait state */
            seState = PUSH_STATE_WAIT;
            break;

        case PUSH_STATE_WAIT:
            /* Check for command */
            if ( PIN_LOGIC_HIGH == gubPins_read(PIN_TRIGGER) )
            {
                /* Check that the flywheels are ready */
                if ( true == gfFlywheel_engaged() )
                {
                    /* Check if cooldown period has expired */
                    if ( suwCooldownTimerMs >= PUSH_COOLDOWN_MS )
                    {
                        /* Move to extend state */
                        seState = PUSH_STATE_EXTEND;
                    }
                }
            }
            break;

        case PUSH_STATE_EXTEND:
            /* Move to retract state if photosensor has cleared or the push timed out */
            if ( (PIN_LOGIC_HIGH == gubPins_read(PIN_PUSH_RETRACTED)) ||
                 (suwTimerMs >= PUSH_OPERATION_TIMEOUT_MS) )
            {
                /* Return to wait state */
                seState = PUSH_STATE_RETRACT;
            }
            break;

        case PUSH_STATE_RETRACT:
            /* Check for photosensor block or timeout */
            if ( (PIN_LOGIC_LOW == gubPins_read(PIN_PUSH_RETRACTED)) ||
                 (suwTimerMs >= PUSH_OPERATION_TIMEOUT_MS) )
            {
                /* Return to wait state */
                seState = PUSH_STATE_WAIT;

                /* Reset cooldown timer */
                suwCooldownTimerMs = 0u;
            }
            break;

        default:
            /* Go to init state */
            seState = PUSH_STATE_INIT;
            break;
    }
}