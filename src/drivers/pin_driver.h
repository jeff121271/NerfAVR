/*
 *	pin_driver.h
 *
 *	Interface for pin_driver.c.
 *
 *	Jeff Campbell
 *	2/13/18
 *
 */

#ifndef PIN_DRIVER_H
#define PIN_DRIVER_H

/* Includes */
#include <stdbool.h>

/* Defines */

/* Enumeration for logic states */
typedef enum pin_state_logic
{
	PIN_LOGIC_OFF = 0,	/* Pin off */
	PIN_LOGIC_ON		/* Pin on */
} pin_state_logic_t;

/* Enumeration for pin direction */
typedef enum pin_state_direction
{
	PIN_DIR_INPUT = 0,	/* Input pin */
	PIN_DIR_OUTPUT		/* Output pin */
} pin_state_direction_t;

/* Enumeration for pin pullup logic */
typedef enum pin_state_pullup
{
	PIN_PULLUP_DISABLED = 0,	/* Pullup disabled */
	PIN_PULLUP_ENABLED			/* Pullup enabled */
} pin_state_pullup_t;

/* Pin driver description data */
typedef struct pin_driver_desc
{
	pin_state_logic_t eLogic;			/* Pin's logic state */
	pin_state_direction_t eDirection;	/* Pin's I/O direction */
	pin_state_pullup_t ePullup;			/* Pin's pullup config */
} pin_driver_desc_t;

/* Pin driver operations */
typedef struct pin_driver_operations
{
	void (*pvSetState)(pin_driver_desc_t *pDescription, pin_state_logic_t eState);	/* Function to set logic state of pin */
	void (*pvProcess)(pin_driver_desc_t *pDescription); 							/* Function to update pin output (if necessary) */
} pin_driver_operations_t;

/* Pin driver structure */
typedef struct pin_driver
{
	pin_driver_desc_t Description;		/* Pin description data */
	pin_driver_operations_t Operations; /* Pin operations */
} pin_driver_t;

/* Global functions */
extern bool gfPin_init(pin_driver_t *pDriver);

extern pin_driver_t pin_PA0;
extern pin_driver_t pin_PA1;

extern pin_driver_t pin_PB0;
extern pin_driver_t pin_PB1;
extern pin_driver_t pin_PB2;
extern pin_driver_t pin_PB3;
extern pin_driver_t pin_PB4;
extern pin_driver_t pin_PB5;
extern pin_driver_t pin_PB6;
extern pin_driver_t pin_PB7;

extern pin_driver_t pin_PD0;
extern pin_driver_t pin_PD1;
extern pin_driver_t pin_PD2;
extern pin_driver_t pin_PD3;
extern pin_driver_t pin_PD4;
extern pin_driver_t pin_PD5;

#endif /* PIN_DRIVER_H_ */