/**
 *  interrupt.h
 *
 *  Interface file for interrupt.c.
 *
 *  Jeff Campbell
 *  2/15/18
 *
 */ 

#ifndef INTERRUPT_H
#define INTERRUPT_H

/* Includes */

/* Defines */

/* Global Functions */
extern void gvINT_init(void);
extern void gvINT_enableFlywheel(void);
extern void gvINT_disableFlywheel(void);

#endif /* #ifndef INTERRUPT_H */