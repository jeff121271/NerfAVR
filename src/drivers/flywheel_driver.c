/**
 *  flywheel_driver.c
 *
 *  Driver for the flywheel system.
 *
 *  Calculations:
 *
 *      Assuming 4 counts per revolution.
 *
 *      Estimate for number of encoder counts to expect in a sampling period:
 *          Counts = v * T / 15,000, where:
 *              v = Motor speed (RPM)
 *              T = Calculation interval (ms)
 *
 *      Conversion from encoder counts to calculated motor speed:
 *          Speed = 15,000 * c / T, where:
 *              c = Number of encoder counts
 *              T = Calculation interval (ms)
 *
 *
 *  Motors will achieve speeds on the order of 10,000 RPM.
 *
 *  Jeff Campbell
 *  2/15/18
 *
 */

/* Includes */
#include <stdint.h>
#include <stdbool.h>
#include "pins.h"
#include "pwm.h"
#include "interrupt.h"
#include "flywheel_driver.h"

/* Prototypes */
void gvFlywheel_process(uint16_t uwCallRateMs);
void gvFlywheel_intHandler(uint8_t ubSelect);
bool gfFlywheel_engaged(void);

/* Local Variables */

/* Desired flywheel speed (in PWM command) */
static uint8_t xubPwmCmd = 0u;

/* Raw quadrature counts from flywheel #1 */
static volatile uint16_t xuwWheel1Counts = 0u;

/* Raw quadrature counts from flywheel #2 */
static volatile uint16_t xuwWheel2Counts = 0u;

/* Flywheel #1 speed (RPM) */
static uint16_t xuwWheel1Speed = 0u;

/* Flywheel #2 speed (RPM) */
static uint16_t xuwWheel2Speed = 0u;

/* State of the flywheel state machine */
static flywheel_states_t xeState = FLY_STATE_INIT;

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
    static uint16_t suwTimerMs = 0u;

    /* Increment timers */
    suwTimerMs += uwCallRateMs;

    /* Process state actions */
    switch (xeState)
    {
        case FLY_STATE_INIT:
            /* Do nothing */
            break;

        case FLY_STATE_IDLE:
            /* Make sure motors are turned off */
            gvPWM_setCmd1(0u);
            gvPWM_setCmd2(0u);

            /* Disable interrupts */
            gvINT_disableFlywheel();

            /* Clear counters */
            xuwWheel1Counts = 0u;
            xuwWheel2Counts = 0u;

            /* Clear timer */
            suwTimerMs = 0u;
            break;

        case FLY_STATE_RAMP_UP:
            /* Drive both motors with commanded speed */
            gvPWM_setCmd1(xubPwmCmd);
            gvPWM_setCmd2(xubPwmCmd);

            /* Enable interrupts */
            gvINT_enableFlywheel();
            break;

        case FLY_STATE_MAINTAIN:
            /* Check if it's time to adjust the flywheel */
            if ( suwTimerMs > FLYWHEEL_CALCULATION_TIME_MS)
            {
                /* Increase slave command if it is slower */
                if ( xuwWheel1Counts > xuwWheel2Counts )
                {
                    gvPWM_increment();
                }
                /* Otherwise, decrement it */
                else
                {
                    gvPWM_decrement();
                }

                /* Update calculated speeds (cast to uint32_t to avoid overflow) */
                xuwWheel1Speed = (uint16_t)(((uint32_t)15000u) * xuwWheel1Counts / FLYWHEEL_CALCULATION_TIME_MS);
                xuwWheel2Speed = (uint16_t)(((uint32_t)15000u) * xuwWheel2Counts / FLYWHEEL_CALCULATION_TIME_MS);

                /* Clear encoder counters */
                xuwWheel1Counts = 0u;
                xuwWheel2Counts = 0u;

                /* Clear timer */
                suwTimerMs = 0u;
            }
            break;

        default:
            /* Do nothing */
            break;
    }

    /* Process state transitions */
    switch (xeState)
    {
        case FLY_STATE_INIT:
            /* Go to idle state */
            xeState = FLY_STATE_IDLE;
            break;

        case FLY_STATE_IDLE:
            /* If trigger is pressed, ramp up */
            if ( PIN_LOGIC_HIGH == gubPins_read(PIN_WHEEL_CMD) )
            {
                xeState = FLY_STATE_RAMP_UP;
            }
            break;

        case FLY_STATE_RAMP_UP:
            /* Proceed immediately to speed maintenance state */
            xeState = FLY_STATE_MAINTAIN;
            break;

        case FLY_STATE_MAINTAIN:
            /* Only exit when trigger is released */
            if ( PIN_LOGIC_LOW == gubPins_read(PIN_WHEEL_CMD) )
            {
                xeState = FLY_STATE_IDLE;
            }
            break;

        default:
            break;
    }
}

/**
 *  void gvFlywheel_intHandler(uint8_t ubSelect)
 *
 *  Description:
 *      Interrupt handler for a flywheel encoder.  Increments
 *      the appropriate encoder counter.
 *
 *  Parameters:
 *      ubSelect = Selects which encoder to count.
 *
 *  Returns:
 *      N/A
 *
 */
void gvFlywheel_intHandler(uint8_t ubSelect)
{
    /* Choose which flywheel to increment */
    if ( FLYWHEEL_SELECT_1 == ubSelect )
    {
        xuwWheel1Counts++;
    }
    else
    {
        xuwWheel2Counts++;
    }
}

/**
 *  bool gfFlywheel_engaged(void)
 *
 *  Description:
 *      Determines if the flywheels are ready to fire a dart.
 *
 *  Parameters:
 *      N/A
 *
 *  Returns:
 *      true if flywheels are ready; false otherwise.
 */
bool gfFlywheel_engaged(void)
{
    /* Only return true if flywheel is in the maintain speed state */
    return (FLY_STATE_MAINTAIN == xeState) ? true : false;
}