/**
 *  pid.c
 *
 *  Implements a kind of PID loop.
 *
 *  Jeff Campbell
 *  2/20/18
 *
 */

/* Includes */
#include <stdint.h>
#include "pid.h"

#ifdef PID_ENABLE

/* Prototypes */
int16_t gswPID_process(int16_t swCurrent, int16_t swDesired, int16_t swP, int16_t swI, int16_t swD, uint16_t uwCallRateMs);

/* Local Variables */

int16_t gswPID_process(int16_t swCurrent, int16_t swDesired, int16_t swP, int16_t swI, int16_t swD, uint16_t uwCallRateMs)
{
    static int16_t sswPreviousError = 0u;
    int16_t swError = 0u;
    int16_t swOutput = 0u;

    /* Calculate error */
    swError = swDesired - swCurrent;

    /* Add proportional gain */
    swOutput += (swP * swError);

    /* Add integral gain */
    swOutput += (swI * swError * (int16_t)uwCallRateMs);

    /* Add differential gain */
    swOutput += (swD * (swError - sswPreviousError) / (int16_t)uwCallRateMs);

    /* Update previous error */
    sswPreviousError = swError;

    /* Return result */
    return swOutput;
}

#endif /* #ifdef PID_ENABLE */