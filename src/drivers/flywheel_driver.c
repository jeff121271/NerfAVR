/**
 *  flywheel_driver.c
 *
 *  Driver for the flywheel system.
 *
 *  Jeff Campbell
 *  2/15/18
 *
 */ 

/* Includes */
#include <stdint.h>
#include "pins.h"
#include "pwm.h"
#include "flywheel_driver.h"

/* Prototypes */
void gvFlywheel_process(uint16_t uwCallRateMs);

/* Local Variables */

/* Desired flywheel speed (in terms of PWM command) */
static uint8_t xubDesiredSpeed = 0u;

/* Raw quadrature counts from flywheel #1 */
static volatile uint8_t xubWheel1Counts = 0u;

/* Raw quadrature counts from flywheel #2 */
static volatile uint8_t xubWheel2Counts = 0u;

/**
 *  void gvFlywheel_process(uint16_t uwCallRateMs)
 *
 *  Description:
 *      State machine for the flywheel driver.
 *
 *  Parameters:
 *      uwCallRateMs = Call rate of function, in ms
 *
 *  Returns:
 *      N/A
 *
 */
void gvFlywheel_process(uint16_t uwCallRateMs)
{
    static flywheel_states_t seState = FLY_STATE_INIT;

    /* Process state actions */
    switch (seState)
    {
        case FLY_STATE_INIT:
            /* Do nothing */
            break;

        case FLY_STATE_IDLE:
            /* Make sure motors are turned off */
            gvPWM_setCmd1(0u);
            gvPWM_setCmd2(0u);
            break;

        case FLY_STATE_RAMP_UP:
            /* Drive both motors with commanded speed */
            gvPWM_setCmd1(xubDesiredSpeed);
            gvPWM_setCmd2(xubDesiredSpeed);
            break;

        case FLY_STATE_MAINTAIN:
            /* Set master command */
            gvPWM_setCmd1(xubDesiredSpeed);

            /* Increase slave command if it is slower */

            /* Otherwise, decrement it */

            break;

        default:
            /* Do nothing */
            break;
    }

    /* Process state transitions */
    switch (seState)
    {
        case FLY_STATE_INIT:
            /* Go to idle state */
            seState = FLY_STATE_IDLE;
            break;

        case FLY_STATE_IDLE:
            /* If trigger is pressed, ramp up */
            if ( PIN_LOGIC_HIGH == gubPins_read(PIN_TRIGGER) )
            {
                seState = FLY_STATE_RAMP_UP;
            }
            break;

        case FLY_STATE_RAMP_UP:
            /* If trigger is released, go to idle */
            if ( PIN_LOGIC_LOW == gubPins_read(PIN_TRIGGER) )
            {
                seState = FLY_STATE_IDLE;
            }
            else
            {
                /* Otherwise, check if master is at speed */
                // TODO: speed calculation
            }
            break;

        case FLY_STATE_MAINTAIN:
            /* Only exit when trigger is released */
            if ( PIN_LOGIC_LOW == gubPins_read(PIN_TRIGGER) )
            {
                seState = FLY_STATE_IDLE;
            }
            break;

        default:
            break;
    }
}