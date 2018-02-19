/*
 *    pins.h
 *
 *    Interface file for pins.c.
 *
 *    Jeff Campbell
 *    2/13/18
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

/* Data direction register value for input */
#define PIN_DIRECTION_INPUT 0u

/* Data direction register value for output */
#define PIN_DIRECTION_OUTPUT 1u

/* Value to disable pullup logic */
#define PIN_PULLUP_DISABLE 0u

/* Value to enable pullup logic */
#define PIN_PULLUP_ENABLE 1u

/* Value for logic level low */
#define PIN_LOGIC_LOW 0u

/* Value for logic level high */
#define PIN_LOGIC_HIGH 1u

/* Struct describing a pin's characteristics */
typedef struct pin_desc
{
    uint8_t logicLevel:1;       /* Logic level */
    uint8_t direction:1;        /* I/O direction */
    uint8_t portSel:2;          /* Port selection (see defines above) */
    uint8_t pullupEnable:1;     /* Pullup logic enable */
    uint8_t pinNum:3;           /* Number of pin */
} pin_desc_t;

/* Enumeration of pin index values */
typedef enum pin_index
{
    PIN_HEARTBEAT = 0,      /* Heartbeat pin */
    PIN_DART_CHAMBER,       /* Dart-in-chamber sensor */
    PIN_PUSH_RETRACTED,     /* Push motor extended sensor */
    PIN_PUSH_CMD_1,         /* Push motor command #1 */
    PIN_PUSH_CMD_2,         /* Push motor command #2 */
    PIN_FLYWHEEL_PWM_1,     /* Flywheel PWM #1 */
    PIN_FLYWHEEL_PWM_2,     /* Flywheel PWM #2 */
    PIN_FLYWHEEL_FB_1,      /* Flywheel #1 feedback */
    PIN_FLYWHEEL_FB_2,      /* Flywheel #2 feedback */
    PIN_TRIGGER,            /* Trigger input */
    PIN_COUNT               /* Number of pins */
} pin_index_t;

/* Global Functions */
extern void gvPins_init(void);
extern void gvPins_updateAll(void);
extern void gvPins_control(pin_index_t ePinIdx, uint8_t ubLogic);
extern void gvPins_toggle(pin_index_t ePinIdx);
extern uint8_t gubPins_read(pin_index_t ePinIdx);

#endif /* #ifndef PINS_H */