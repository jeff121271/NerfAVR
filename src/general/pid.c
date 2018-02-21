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
int16_t gswPID_process(int16_t swCurrent, int16_t swDesired, int16_t *pswPreviousError, int16_t swP, int16_t swI, int16_t swD, uint16_t uwCallRateMs);

/* Local Variables */

/**
 *  int16_t gswPID_process(int16_t swCurrent, int16_t swDesired, int16_t swPreviousError, int16_t swP, int16_t swI, int16_t swD, uint16_t uwCallRateMs)
 *
 *  Description:
 *      Implements one iteration of a PID control loop.
 *
 *  Parameters:
 *      swCurrent = Current output feedback
 *      swDesired = Desired output level
 *      pswPreviousError = Pointer to previous error level
 *      swP = Proportional gain constant
 *      swI = Integral gain constant
 *      swD = Differential gain constant
 *      uwCallRateMs = Sampling rate of the loop
 *
 *  Returns:
 *      Output command of the loop.  Also updates pswPreviousError.
 *
 */
int16_t gswPID_process(int16_t swCurrent, int16_t swDesired, int16_t *pswPreviousError, int16_t swP, int16_t swI, int16_t swD, uint16_t uwCallRateMs)
{
    int16_t swError = 0u;
    int16_t swOutput = 0u;

    /* Calculate error */
    swError = swDesired - swCurrent;

    /* Add proportional gain */
    swOutput += (swP * swError);

    /* Add integral gain */
    swOutput += (swI * swError * (int16_t)uwCallRateMs);

    /* Add differential gain */
    swOutput += (swD * (swError - (*pswPreviousError)) / (int16_t)uwCallRateMs);

    /* Update previous error */
    *pswPreviousError = swError;

    /* Return result */
    return swOutput;
}

#endif /* #ifdef PID_ENABLE */