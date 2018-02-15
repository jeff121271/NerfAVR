/**
 *  tasks.c
 *
 *  Contains definitions of all tasks that will be performed.
 *
 *  Jeff Campbell
 *  1/31/18
 */

/* Includes */
#include <stdint.h>
#include "pins.h"
#include "tasks.h"

/* Prototypes */
void gvTasks_pinUpdate(uint16_t uwCallRateMs);

/* Local Variables */

/**
 *    void gvTasks_pinUpdate(uint16_t uwCallRateMs)
 *
 *    Description:
 *        Calls the pin update function.
 *
 *    Parameters:
 *        uwCallRateMs = Call rate of function, in ms
 *
 *    Returns:
 *        N/A
 *
 */
void gvTasks_pinUpdate(uint16_t uwCallRateMs)
{
    static uint16_t suwTimerMs = 0u;

    /* Update timer */
    suwTimerMs += uwCallRateMs;

    /* Check for heartbeat time */
    if ( suwTimerMs >= TASKS_HEARTBEAT_RATE_MS )
    {
        /* Toggle heartbeat bit */
        gvPins_toggle(PIN_HEARTBEAT);

        /* Clear timer */
        suwTimerMs = 0u;
    }

    /* Call pin update function */
    gvPins_updateAll();
}