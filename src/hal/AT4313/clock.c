/**
 *  clock.c
 *
 *  Contains code for interacting with the system clock.
 *
 *    Timer 1 will be used as the clock here.
 *
 *  Jeff Campbell
 *  2/1/18
 *
 */

/* Includes */
#include <avr/io.h>
#include "clock.h"

/* Prototypes */
void gvClock_init(void);
uint16_t guwClock_read(void);
uint16_t guwClock_getDeltaUs(uint16_t uwStart, uint16_t uwEnd);

/* Local Variables */

/**
 *  void gvClock_init(void)
 *
 *  Description:
 *      Initialize the clock system.
 *      Target frequency: 8MHz
 *
 *  Parameters:
 *      N/A
 *
 *  Returns:
 *      N/A
 *
 */
void gvClock_init(void)
{
    /* Oscillator configuration: 8MHz loaded by hardware at reset */
    OSCCAL = CLOCK_OSC_MAX_FREQ;

    /* Enable clock prescaler change */
    CLKPR |= 1 << CLKPCE;

    /* Set clock prescaler to zero (Divider = 1) */
    CLKPR = 0u;

    /* Enable Timer 1 with no clock divider */
    TCCR1B |= 1u << CS10;
}

/**
 *    uint16_t guwClock_getDeltaUs(uint16_t uwStart, uint16_t uwEnd)
 *
 *    Description:
 *        Calculates the difference, in microseconds, between two clock values.
 *
 *    Parameters:
 *        uwStart = Starting value
 *        uwEnd = Ending value
 *
 *    Returns:
 *        The difference in microseconds
 *
 */
uint16_t guwClock_getDeltaUs(uint16_t uwStart, uint16_t uwEnd)
{
    uint16_t uwResult;

    /* Get the difference between start and end */
    uwResult = uwEnd - uwStart;

    /* Correct difference in the event of an overflow */
    if ( uwEnd < uwStart )
    {
        uwResult = (0xFFFFu - uwEnd) + uwStart;
    }

    /* Return result */
    return uwResult;
}

/**
 *    uint16_t guwClock_read(void)
 *
 *    Description:
 *        Reads the current value of the 16-bit clock.
 *
 *    Parameters:
 *        N/A
 *
 *    Returns:
 *        The current clock value.
 *
 */
uint16_t guwClock_read(void)
{
    /* Return current counter status */
    return (uint16_t)TCNT1;
}