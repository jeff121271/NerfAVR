/**
 *  clock.h
 *
 *  Interface for clock.c.
 *
 *  Jeff Campbell
 *  2/1/18
 *
 */

#ifndef CLOCK_H
#define CLOCK_H

/* Includes */

/* Defines */

/* OSCCAL value for maximum frequency */
#define CLOCK_OSC_MAX_FREQ 0x7Fu

/* Clock SEL config for external clock */
#define CLOCK_SEL_EXTERNAL 0x0u

/* Clock SEL config for internal 4MHz clock */
#define CLOCK_SEL_INT_4MHZ 0x2u

/* Clock SEL config for internal 8MHz clock */
#define CLOCK_SEL_INT_8MHZ 0x4u

/* Clock SEL config for internal 128kHz clock */
#define CLOCK_SEL_INT_128KHZ 0x6u

/* Global Functions */
extern void gvClock_init(void);

#endif /* #ifndef CLOCK_H */
