/**
 *    timer.c
 *
 *    Used in timer logic.  This is the implementation
 *    for the AT4313 chip.
 *
 *    Jeff Campbell
 *    1/31/18
 *
 */

/* Includes */
#include <stdint.h>
#include "clock.h"
#include "timer.h"

/* Prototypes */
void gvTimer_sleepMs(uint16_t uwTimeMs, uint16_t uwStartOverride);

/* Local Variables */

/**
 *    void gvTimer_sleepMs(uint16_t uwTimeMs, uint16_t uwStartOverride)
 *
 *    Description:
 *        Sleeps for the given amount of time.
 *
 *    Parameters:
 *        uwTimeMs = Time to sleep, in ms.
 *        uwStartOverride = Override value for starting time
 *
 *    Returns:
 *        N/A
 *
 */
void gvTimer_sleepMs(uint16_t uwTimeMs, uint16_t uwStartOverride)
{
    uint16_t uwStart = 0u;
    uint16_t uwEnd = 0u;
    uint16_t uwEndTime = 0u;

    /* Get start time */
    uwStart = guwClock_read();
    uwEnd = uwStart;

    /* Override start time if necessary */
    if ( TIMER_OVERRIDE_SKIP != uwStartOverride )
    {
        uwStart = uwStartOverride;
    }

    /* Calculate end time */
    uwEndTime = (uwTimeMs * 1000u) - 50u;

    /* Loop until request time has passed */
    while ( uwEndTime > guwClock_getDeltaUs(uwStart, uwEnd) )
    {
        uwEnd = guwClock_read();
    }
}