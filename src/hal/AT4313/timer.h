/**
 *    timer.h
 *
 *    Interface for timer.c.
 *
 *    Jeff Campbell
 *    1/31/18
 *
 */

#ifndef TIMER_H
#define TIMER_H

/* Includes */

/* Defines */

/* Value to not use timer override feature */
#define TIMER_OVERRIDE_SKIP 0xFFFFu

/* Global Functions */
extern void gvTimer_sleepMs(uint16_t uwTimeMs, uint16_t uwStartOverride);

#endif /* #ifndef TIMER_H */