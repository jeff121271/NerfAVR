/**
 *  clock.c
 *
 *  Contains code for interacting with the system clock.
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


    /* Enable clock prescaler change */
    CLKPR |= CLKPCE;

    /* Set clock prescaler to zero (Divider = 1) */
    CLKPR = 0u;
}