/**
 *  pwm.c
 *
 *  Contains PWM logic.  Currently written to use Timer 0 (8-bit).
 *
 *  Tentative theory for how the two flywheels will be controlled:
 *      Flywheel 1 will be the "master" wheel.  It sets the pace.
 *      Flywheel 2 will be the "slave" wheel.  It will continually
 *      adjust to try and match flywheel 1.
 *
 *  Jeff Campbell
 *  2/15/18
 *
 */

/* Includes */
#include <stdint.h>
#include <avr/io.h>
#include "pwm.h"

/* Prototypes */
void gvPWM_init(void);
void gvPWM_setCmd1(uint8_t ubCmd);
void gvPWM_setCmd2(uint8_t ubCmd);
void gvPWM_increment(void);
void gvPWM_decrement(void);

/* Local Variables */

/**
 *  void gvPWM_init(void)
 *
 *  Description:
 *      Initializes the PWM system.
 *
 *  Parameters:
 *      N/A
 *
 *  Returns:
 *      N/A
 *
 */
void gvPWM_init(void)
{
    /* Set clock source (no prescaling) */
    TCCR0B |= 1u << CS00;

    /* Enable fast PWM mode with TOP as max register value (WGM02:0 = 3) */
    TCCR0B |= 0u << WGM02;
    TCCR0A |= 1u << WGM01;
    TCCR0A |= 1u << WGM00;

    /* Set OC0A compare mode - clear on match, set at TOP */
    TCCR0A |= 1u << COM0A1;
    TCCR0A |= 0u << COM0A0;

    /* Set OC0B compare mode - clear on match, set at TOP */
    TCCR0B |= 1u << COM0B1;
    TCCR0B |= 0u << COM0B0;

    /* Clear PWM registers */
    OCR0A = 0u;
    OCR0B = 0u;
}

/**
 *  void gvPWM_setCmd1(uint8_t ubCmd)
 *
 *  Description:
 *      Updates the PWM rate for flywheel 1.
 *
 *  Parameters:
 *      ubCmd = The new command
 *
 *  Returns:
 *      N/A
 *
 */
void gvPWM_setCmd1(uint8_t ubCmd)
{
    /* Update PWM register */
    OCR0A = ubCmd;
}

/**
 *  void gvPWM_setCmd2(uint8_t ubCmd)
 *
 *  Description:
 *      Updates the PWM rate for flywheel 2.
 *
 *  Parameters:
 *      ubCmd = The new command
 *
 *  Returns:
 *      N/A
 *
 */
void gvPWM_setCmd2(uint8_t ubCmd)
{
    /* Update PWM register */
    OCR0B = ubCmd;
}

/**
 *  void gvPWM_increment(void)
 *
 *  Description:
 *      Increments the slave flywheel PWM signal.
 *
 *  Parameters:
 *      N/A
 *
 *  Returns:
 *      N/A
 *
 */
void gvPWM_increment(void)
{
    /* Check that value is not maxed out */
    if ( PWM_MAX_COMP_VALUE > OCR0B )
    {
        /* Increment OC0B compare register */
        OCR0B = OCR0B + 1u;
    }
}

/**
 *  void gvPWM_decrement(void)
 *
 *  Description:
 *      Decrements the slave flywheel PWM signal.
 *
 *  Parameters:
 *      N/A
 *
 *  Returns:
 *      N/A
 *
 */
void gvPWM_decrement(void)
{
    /* Check for underflow */
    if ( PWM_MIN_COMP_VALUE < OCR0B )
    {
        /* Decrement OC0B compare register */
        OCR0B = OCR0B - 1u;
    }
}