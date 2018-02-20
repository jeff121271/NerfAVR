/**
 *  pid.h
 *
 *  Interface file for pid.c.
 *
 *  Jeff Campbell
 *  2/20/18
 *
 */

#ifndef PID_H
#define PID_H
#ifdef PID_ENABLE

/* Includes */
#include <stdint.h>

/* Defines */

/* Global Functions */
int16_t gswPID_process(int16_t swCurrent, int16_t swDesired, int16_t swP, int16_t swI, int16_t swD, uint16_t uwCallRateMs);

#endif /* #ifdef PID_ENABLE */
#endif /* #ifndef PID_H */