/*
 *	pins.h
 *
 *	Interface file for pins.c.
 *
 *	Jeff Campbell
 *	2/13/18
 *
 */

#ifndef PINS_H
#define PINS_H

/* Includes */
#include <stdint.h>

/* Defines */

/* Pattern to select Port A */
#define PIN_SELECT_PORTA 0u

/* Pattern to select Port B */
#define PIN_SELECT_PORTB 1u

/* Pattern to select Port D */
#define PIN_SELECT_PORTD 2u

#define PIN_DIRECTION_INPUT 0u
#define PIN_DIRECTION_OUTPUT 1u

#define PIN_PULLUP_DISABLE 0u
#define PIN_PULLUP_ENABLE 1u

#define PIN_LOGIC_LOW 0u
#define PIN_LOGIC_HIGH 1u

/* Struct describing a pin's characteristics */
typedef struct pin_desc
{
	uint8_t logicLevel:1;		/* Logic level */
	uint8_t direction:1;		/* I/O direction */
	uint8_t portSel:2;			/* Port selection (see defines above) */
	uint8_t pullupEnable:1;		/* Pullup logic enable */
	uint8_t pinNum:3;			/* Number of pin */
} pin_desc_t;

/* Enumeration of pin index values */
typedef enum pin_index
{
	PIN_TEST_OUTPUT = 0u,
	PIN_NUMBER
} pin_index_t;

/* Global Functions */
extern void gvPins_init(void);
extern void gvPins_updateAll(void);

#endif /* #ifndef PINS_H */